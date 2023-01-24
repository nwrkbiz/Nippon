#pragma once

#include <string>
#include <vector>

#include <Common/Types.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace ark
{
  class CorruptionUtils
  {
  public:

    static U32 Crc32(const std::string& String, U64 DefaultChunkSize = (4ULL * 1024ULL));
    static U32 Crc32(const std::vector<U8>& Bytes, U64 DefaultChunkSize = (4ULL * 1024ULL));
  };
}