// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com

#include <auto_complete_client.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>

AutoCompleteClient::AutoCompleteClient(std::string host, std::string port)
  : m_host(std::move(host)), m_port(std::move(port)) {}

nlohmann::json AutoCompleteClient::sendRequest([[maybe_unused]] std::string_view username,
                                               std::string_view request) {
  boost::asio::io_context ioc{};

  boost::asio::ip::tcp::resolver resolver(ioc);
  boost::beast::tcp_stream stream(ioc);

  const auto result = resolver.resolve(m_host, m_port);

  stream.connect(result);

  boost::beast::http::request<boost::beast::http::string_body> req{
      boost::beast::http::verb::post, "/v1/api/suggest", 11};
  req.set(boost::beast::http::field::host, m_host);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(boost::beast::http::field::content_type, "application/json");
  req.body() = R"({"input": ")" + std::string(request) + R"("})";
  req.prepare_payload();

  boost::beast::http::write(stream, req);

  boost::beast::flat_buffer buffer;
  boost::beast::http::response<boost::beast::http::string_body> res;

  boost::beast::http::read(stream, buffer, res);

  boost::beast::error_code ec;
  stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

  if(ec && ec != boost::beast::errc::not_connected)
    throw boost::beast::system_error{ec};

  return nlohmann::json::parse(res.body());
}