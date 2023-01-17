#pragma once

#include <filesystem>

#include <Common/Common.h>
#include <Common/Types.h>
#include <Common/BinaryReader.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace ark
{
  namespace fs = std::filesystem;

  #pragma pack(push, 1)
  struct ObjectTableEntry
  {
    U8 Id; // lots of values 00-fe 
    U8 Category; // category id - which folder it comes from
    U8 Unknown3; // 00, 10, 20, 30, 40, 50, 60, 70, 80, 90
    U8 Unknown4; // always 00
    PackedTuple<U8> Scale;
    PackedTuple<U8> Rotation;
    PackedTuple<U16> Position;
    U32 Unknown5; // a lot of values, only first byte is used.
    U32 Unknown6; // a lot of values, only first byte is used.
    U8 Unknown7; // 00-0c
    U8 Unknown8; // lots of values
    U8 Unknown9; // bunch, 0*, 4* or 70 (not all values of * though)
    U8 UnknownA; // lots of values
  };
  #pragma pack(pop)

  class ObjectTableParser
  {
  public:

    ObjectTableParser(const fs::path& File);

  public:

    inline auto begin() { return mObjects.begin(); }
    inline const auto begin() const { return mObjects.cbegin(); }

    inline auto end() { return mObjects.end(); }
    inline const auto end() const { return mObjects.cend(); }

  private:

    BinaryReader mBinaryReader;
    std::vector<ObjectTableEntry> mObjects;
  };
}