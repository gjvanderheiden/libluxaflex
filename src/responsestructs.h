#pragma once
#include <vector>
#include "objectstructs.h"

struct ShadesResponse {
  std::vector<Shade> shadeData;
};

struct ScenesResponse {
  std::vector<Scene> sceneData;
};
