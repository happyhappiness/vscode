std::string
Manager::proxy_address() const {
  return rak::socket_address::cast_from(torrent::connection_manager()->proxy_address())->address_str();
}