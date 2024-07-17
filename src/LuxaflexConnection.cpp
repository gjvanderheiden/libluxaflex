#include "LuxaflexConnection.h"
#include "base64.h"
#include "cpp_yyjson.hpp"
#include <asio.hpp>
#include <iterator>
#include <requeststructs.h>
#include <responsestructs.h>

LuxaflexConnection::LuxaflexConnection(std::string host,
                                       asio::io_context &io_context)
    : socket{io_context} {
  tcp::resolver resolver(io_context);
  socket.connect(resolver.resolve(host, "80")->endpoint());
}

std::string LuxaflexConnection::callRest(std::string method, std::string path,
                                         std::string_view requestContent) {
  std::string request(method);
  request.append(" ");
  request.append(path);
  request.append(" HTTP/1.1\r\n"
                 "Host: 192.168.10.46:80\r\n"
                 "Content-Type: application/json; charset=utf-8\r\n"
                 "Content-Length: ");
  request.append(std::to_string(requestContent.size()));
  request.append("\r\n\r\n");
  request.append(requestContent);

  size_t bytesSend = socket.write_some(asio::buffer(request));

  std::array<std::uint8_t, 4096> reply;
  size_t reply_length = socket.read_some(asio::buffer(reply));
  std::string replyString;
  std::copy(reply.begin(), reply.begin() + reply_length,
            std::back_inserter(replyString));

  auto index = replyString.find_last_of("\r\n\r\n");
  return replyString.substr(index);
}

std::vector<Shade> LuxaflexConnection::getShades() {
  auto val = yyjson::read(callRest("GET", "/api/shades"));
  auto response = yyjson::cast<ShadesResponse>(val).shadeData;
  for (Shade &shade : response) {
    shade.name = base64_decode(shade.name);
  }
  return response;
}

std::vector<Scene> LuxaflexConnection::getScenes() {
  auto val = yyjson::read(callRest("GET", "/api/scenes"));
  auto response = yyjson::cast<ScenesResponse>(val).sceneData;
  for (Scene &scene : response) {
    scene.name = base64_decode(scene.name);
  }
  return response;
}

void LuxaflexConnection::moveShade(int shadeId, Motion motion) {
  std::string path = "/api/shades/";
  path.append(std::to_string(shadeId));
  std::string json("{\"shade\":{\"motion\":\"");
  json.append(toString(motion));
  json.append("\"}}");
  callRest("PUT", path, json);
}

void LuxaflexConnection::moveShade(int shadeId, Positions positions) {
  UpdateShadeRequest request;
  request.shade.positions = positions;
  auto object = yyjson::object(request);
  std::string path = "/api/shades/";
  path.append(std::to_string(shadeId));
  callRest("PUT", path, object.write());
}
