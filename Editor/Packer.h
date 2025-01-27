#pragma once

#include <set>
#include <filesystem>

#include <Common/Types.h>

#include <Vendor/rapidjson/rapidjson.h>

///////////////////////////////////////////////////////////
// Namespaces
///////////////////////////////////////////////////////////

namespace fs = std::filesystem;
namespace rj = rapidjson;

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace ark
{
  class Packer
  {
  public:

    static void Unpack();
    static void Repack();

  public:

    static void CheckIntegrity();
    static void GenerateIntegrityMap();
  };
}