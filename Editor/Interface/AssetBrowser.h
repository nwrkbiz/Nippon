#pragma once

#include <Editor/Interface.h>

///////////////////////////////////////////////////////////
// Definition
///////////////////////////////////////////////////////////

namespace ark
{
  class AssetBrowser : public Interface
  {
  public:

    virtual void Update() override;
    virtual void Draw() override;
  };
}