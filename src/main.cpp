#include "LuxaflexConnection.h"
#include <iostream>
#include <objectstructs.h>

int main() {
  try {
    asio::io_context io_context;
    LuxaflexConnection luxaflexConnection("192.168.10.46", io_context);
    std::cout << "Shades:\n";
    for (Shade &shade : luxaflexConnection.getShades()) {
      std::cout << " - name       : " << shade.name << "\n";
      std::cout << " - id         : "   << shade.id   << "\n";
      std::cout << " - position 1 : " << shade.positions.position1 << "\n";
      std::cout << " - postype  1 : " << shade.positions.posKind1  << "\n";
      std::cout << " - position 2 : " << shade.positions.position2 << "\n";
      std::cout << " - postype  2 : " << shade.positions.posKind2  << "\n\n";
    }

    std::cout << "\nScenes:\n";
    for(Scene &scene : luxaflexConnection.getScenes()) {
      std::cout << " - name : " << scene.name << "\n";
      std::cout << " - id   : "   << scene.id   << "\n\n";
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
