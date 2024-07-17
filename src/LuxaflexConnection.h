#pragma once
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <string>
#include "objectstructs.h"

using asio::ip::tcp;

class LuxaflexConnection {
public:
  LuxaflexConnection(std::string host, 
    asio::io_context& io_context);

  std::vector<Shade> getShades();
  void moveShade(int shadeId, Motion motion);
  void moveShade(int shadeId, Positions positions);

  std::vector<Scene> getScenes();

private:
  std::string callRest(std::string method, std::string path, std::string_view content="");
  tcp::socket socket;
};
