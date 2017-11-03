void
apply_scgi(const std::string& arg, int type) {
  if (control->scgi() != NULL)
    throw torrent::input_error("SCGI already enabled.");

  if (!rpc::xmlrpc.is_valid())
    initialize_xmlrpc();

  // Fix this...
  control->set_scgi(new rpc::SCgi);

  rak::address_info* ai = NULL;
  rak::socket_address sa;
  rak::socket_address* saPtr;

  try {
    int port, err;
    char dummy;
    char address[1024];

    switch (type) {
    case 1:
      if (std::sscanf(arg.c_str(), ":%i%c", &port, &dummy) == 1) {
        sa.sa_inet()->clear();
        saPtr = &sa;

      } else if (std::sscanf(arg.c_str(), "%1023[^:]:%i%c", address, &port, &dummy) == 2) {
        if ((err = rak::address_info::get_address_info(address, PF_INET, SOCK_STREAM, &ai)) != 0)
          throw torrent::input_error("Could not bind address: " + std::string(rak::address_info::strerror(err)) + ".");

        saPtr = ai->address();

      } else {
        throw torrent::input_error("Could not parse address.");
      }

      if (port <= 0 || port >= (1 << 16))
        throw torrent::input_error("Invalid port number.");

      saPtr->set_port(port);
      control->scgi()->open_port(saPtr, saPtr->length(), rpc::call_command_value("get_scgi_dont_route"));

      break;

    case 2:
    default:
      control->scgi()->open_named(rak::path_expand(arg));
      break;
    }

    rak::address_info::free_address_info(ai);

  } catch (torrent::local_error& e) {
    rak::address_info::free_address_info(ai);

    throw torrent::input_error(e.what());
  }

  control->scgi()->set_slot_process(rak::mem_fn(&rpc::xmlrpc, &rpc::XmlRpc::process));
}