void
Manager::set_proxy_address(const std::string& addr) {
  int port;
  rak::address_info* ai;

  char buf[addr.length() + 1];

  int err = std::sscanf(addr.c_str(), "%[^:]:%i", buf, &port);

  if (err <= 0)
    throw torrent::input_error("Could not parse proxy address.");

  if (err == 1)
    port = 80;

  if ((err = rak::address_info::get_address_info(buf, PF_INET, SOCK_STREAM, &ai)) != 0)
    throw torrent::input_error("Could not set proxy address: " + std::string(rak::address_info::strerror(err)) + ".");
  
  try {

    ai->address()->set_port(port);
    torrent::connection_manager()->set_proxy_address(ai->address()->c_sockaddr());
    
    rak::address_info::free_address_info(ai);

  } catch (torrent::input_error& e) {
    rak::address_info::free_address_info(ai);
    throw e;
  }
}