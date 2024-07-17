#pragma once
#include <string>

enum class Motion {
  own, 
  heart,
  jog,
  leftTilt,
  rightTilt,
  stop,
  up
};

struct Positions {
  int position1;
  int position2;
  int posKind1;
  int posKind2;
};

struct Shade {
  int id;
  int type;
  int capablitities;
  int batteryKind;
  int batteryStatus;
  int roomId;
  std::string name;
  int groupId;
  int signalStrength;
  Positions positions; 
};

struct Scene {
  int colorId;
  int iconId;
  int id;
  std::string name;
  int networkNumber;
  int roomId;
};
