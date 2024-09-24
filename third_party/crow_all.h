// third_party/crow_all.h
#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>

namespace crow {

    
    namespace json {
        class wvalue {
        public:
            std::unordered_map<std::string, std::string> data;

            std::string s() const {
                return boost::lexical_cast<std::string>(data.at("pdf_file"));
            }

            static wvalue load(const std::string& body) {
                wvalue v;
                std::stringstream ss(body);
                std::string key, value;
                while (ss >> key >> value) {
                    boost::replace_all(key, "\"", "");
                    boost::replace_all(value, "\"", "");
                    v.data[key] = value;
                }
                return v;
            }
        };
    }

    using namespace boost::beast;

    
    class SimpleApp {
    public:
        SimpleApp() : ioc_(), acceptor_(ioc_, tcp::endpoint(tcp::v4(), 8080)) {}

        // Define a route for POST requests
        template<typename Handler>
        void route(const std::string& route_path, Handler handler) {
            routes_[route_path] = handler;
        }

        // Method to handle HTTP methods
        void handle_request(tcp::socket socket, http::request<http::string_body> req) {
            auto route = routes_.find(req.target().to_string());
            if (route != routes_.end()) {
                crow::response res = route->second(req);
                send_response(std::move(socket), res);
            } else {
                crow::response res(404, "Not Found");
                send_response(std::move(socket), res);
            }
        }

        
        void run() {
            accept();
            ioc_.run();
        }

    private:
        boost::asio::io_context ioc_;
        tcp::acceptor acceptor_;
        std::unordered_map<std::string, std::function<crow::response(const crow::request&)>> routes_;

        void accept() {
            acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    read_request(std::move(socket));
                }
                accept();
            });
        }

        void read_request(tcp::socket socket) {
            auto req = std::make_shared<http::request<http::string_body>>();
            http::async_read(socket, buffer_, *req, [this, socket = std::move(socket), req](boost::system::error_code ec, std::size_t) mutable {
                if (!ec) {
                    handle_request(std::move(socket), *req);
                }
            });
        }

        void send_response(tcp::socket socket, const crow::response& res) {
            auto response = std::make_shared<http::response<http::string_body>>(http::response<http::string_body>(http::status::ok, 11));
            response->set(http::field::content_type, "application/json");
            response->body() = res.body;
            response->content_length(response->body().size());

            http::async_write(socket, *response, [socket = std::move(socket), response](boost::system::error_code, std::size_t) {});
        }
    };

    
    struct response {
        std::string body;
        int code;

        response(int code, const std::string& body) : code(code), body(body) {}
    };

    struct request {
        std::string body;
    };

    
    namespace HTTPMethod {
        static const int Post = 1;
    }
}


#define CROW_ROUTE(app, route) \
    app.route(route, [&](const crow::request& req)

