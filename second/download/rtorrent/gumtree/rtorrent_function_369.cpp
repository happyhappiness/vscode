void
Manager::receive_http_failed(std::string msg) {
  push_log_std("Http download error: \"" + msg + "\"");
}