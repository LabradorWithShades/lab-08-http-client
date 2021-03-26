// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com

#ifndef INCLUDE_AUTO_COMPLETE_CLIENT_HPP_
#define INCLUDE_AUTO_COMPLETE_CLIENT_HPP_

#include <nlohmann/json.hpp>
#include <boost/asio/ip/tcp.hpp>

class AutoCompleteClient {
 public:
  AutoCompleteClient(std::string host, std::string port);
  nlohmann::json sendRequest(std::string_view username,
                             std::string_view request);

 private:
  std::string m_host;
  std::string m_port;
};

#endif  // INCLUDE_AUTO_COMPLETE_CLIENT_HPP_
