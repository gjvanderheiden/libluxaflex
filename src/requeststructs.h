#pragma once
#include "objectstructs.h"
#include <string>


inline std::string toString(Motion motion) {
  switch(motion) {
    case Motion::own:
    return "own";
    case Motion::heart:
    return "heart";
    case Motion::jog:
    return "jog";
    case Motion::leftTilt:
    return "leftTilt";
    case Motion::rightTilt:
    return "rightTilt";
    case Motion::stop:
    return "stop";
    case Motion::up:
    return "up";
  }
}
inline Motion toMotion(std::string motion) {
  if("own" == motion) {
    return Motion::own;
  } else if ("heart" == motion) {
    return Motion::heart;
  } else if ("jog" == motion) {
    return Motion::jog;
  } else if ("leftTilt" == motion) {
    return Motion::leftTilt;
  } else if ("stop" == motion) {
    return Motion::stop;
  } else if ("up" == motion) {
    return Motion::up;
  } else {
    throw std::exception();
  }
}

struct UpdateShadeRequest {
  struct ShadeUpdate {
    Positions positions;
  } shade;
};
