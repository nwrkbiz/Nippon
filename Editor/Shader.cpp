#include <Common/Debug.h>

#include <Common/Utils/FileUtils.h>

#include <Editor/Shader.h>

#include <Vendor/GLAD/glad.h>

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace ark
{
  Shader::Shader(const fs::path& File)
  {
    std::string vertexShader;
    std::string fragmentShader;

    ExtractShaderStages(File, vertexShader, fragmentShader);

    mProgram = glCreateProgram();

    U32 vid = glCreateShader(GL_VERTEX_SHADER);
    U32 fid = glCreateShader(GL_FRAGMENT_SHADER);

    char const* vertexShaderPtr = &vertexShader[0];
    glShaderSource(vid, 1, &vertexShaderPtr, nullptr);
    glCompileShader(vid);
    U32 vsCompileStatus = CheckCompileStatus(vid);

    char const* fragmentShaderPtr = &fragmentShader[0];
    glShaderSource(fid, 1, &fragmentShaderPtr, nullptr);
    glCompileShader(fid);
    U32 fsCompileStatus = CheckCompileStatus(fid);

    U32 shaderLinkStatus = 0;
    if (vsCompileStatus && fsCompileStatus)
    {
      glAttachShader(mProgram, vid);
      glAttachShader(mProgram, fid);
      glLinkProgram(mProgram);
      shaderLinkStatus = CheckLinkStatus(mProgram);
    }

    glDeleteShader(vid);
    glDeleteShader(fid);

    if (!shaderLinkStatus)
    {
      glDeleteProgram(mProgram);
      mProgram = 0;
    }
  }

  Shader::~Shader()
  {
    glDeleteProgram(mProgram);
    mProgram = 0;
  }

  void Shader::Bind() const
  {
    glUseProgram(mProgram);
  }

  void Shader::UnBind() const
  {
    glUseProgram(0);
  }

  void Shader::ExtractShaderStages(const fs::path& ShaderFile, std::string& VertexShader, std::string& FragmentShader)
  {
    std::string shaderSource = FileUtils::ReadText(ShaderFile.string());
    std::regex regex = std::regex{ "([^@]*[^@])" };
    std::smatch matches = {};

    while (std::regex_search(shaderSource, matches, regex))
    {
      if (matches.size() == 2)
      {
        if (std::strncmp(matches[0].str().c_str(), "vertex", 6) == 0)
        {
          VertexShader = matches[0].str().substr(7);
        }

        if (std::strncmp(matches[0].str().c_str(), "fragment", 8) == 0)
        {
          FragmentShader = matches[0].str().substr(9);
        }
      }

      shaderSource = matches.suffix();
    }
  }

  U32 Shader::CheckCompileStatus(U32 Sid)
  {
    I32 compileStatus = 0;
    I32 infoLogLength = 0;

    std::string log = "";

    glGetShaderiv(Sid, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == 0)
    {
      glGetShaderiv(Sid, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0)
      {
        log.resize(infoLogLength);

        glGetShaderInfoLog(Sid, infoLogLength, &infoLogLength, &log[0]);

        LOG("%s\n", &log[0]);

        return 0;
      }
    }

    return 1;
  }

  U32 Shader::CheckLinkStatus(U32 Pid)
  {
    I32 compileStatus = 0;
    I32 infoLogLength = 0;

    std::string log = "";

    glGetProgramiv(Pid, GL_LINK_STATUS, &compileStatus);
    if (compileStatus == 0)
    {
      glGetProgramiv(Pid, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0)
      {
        log.resize(infoLogLength);

        glGetProgramInfoLog(Pid, infoLogLength, &infoLogLength, &log[0]);

        LOG("%s\n", &log[0]);

        return 0;
      }
    }

    return 1;
  }

  void Shader::SetUniformR32(const std::string& Name, R32 Value) const
  {
    glUniform1f(
      glGetUniformLocation(mProgram, Name.c_str()),
      Value
    );
  }

  void Shader::SetUniformR32M4(const std::string& Name, R32M4 Value) const
  {
    glUniformMatrix4fv(
      glGetUniformLocation(mProgram, Name.c_str()),
      1,
      0,
      &Value[0][0]
    );
  }
}