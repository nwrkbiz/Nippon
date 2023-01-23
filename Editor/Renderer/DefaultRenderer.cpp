#include <filesystem>

#include <Editor/Mesh.h>
#include <Editor/Scene.h>
#include <Editor/Shader.h>
#include <Editor/Vertex.h>

#include <Editor/Components/Camera.h>
#include <Editor/Components/Transform.h>

#include <Editor/Renderer/DefaultRenderer.h>

///////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////

extern ark::DefaultRenderer* gDefaultRenderer;

///////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////

namespace ark
{
  namespace fs = std::filesystem;

  DefaultRenderer::DefaultRenderer()
    : mShader{ new Shader{ fs::path{ SHADER_DIR } / "Default.glsl" } }
  {

  }

  DefaultRenderer::~DefaultRenderer()
  {
    delete mShader;
  }

  void DefaultRenderer::AddRenderTask(const RenderTask& RenderTask)
  {
    gDefaultRenderer->mRenderQueue.emplace(RenderTask);
  }

  void DefaultRenderer::Render()
  {
    while (!mRenderQueue.empty())
    {
      RenderTask& renderTask = mRenderQueue.front();

      if (renderTask.TransformPtr && renderTask.MeshPtr)
      {
        Camera* camera = Scene::GetMainCamera();

        if (camera)
        {
          mShader->Bind();

          mShader->SetUniformR32M4("UniformProjectionMatrix", camera->GetProjectionMatrix());
          mShader->SetUniformR32M4("UniformViewMatrix", camera->GetViewMatrix());
          mShader->SetUniformR32M4("UniformModelMatrix", renderTask.TransformPtr->GetModelMatrix());

          renderTask.MeshPtr->Bind();
          renderTask.MeshPtr->Render(RenderMode::eRenderModeTriangles);
          renderTask.MeshPtr->UnBind();

          mShader->UnBind();
        }
      }

      mRenderQueue.pop();
    }
  }
}