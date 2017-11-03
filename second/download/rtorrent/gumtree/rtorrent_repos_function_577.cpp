void
Manager::listen_open() {
  // This stuff really should be moved outside of manager, make it
  // part of the init script.
  if (!rpc::call_command_value("get_port_open"))
    return;

  int portFirst, portLast;
  torrent::Object portRange = rpc::call_command_void("get_port_range");

  if (portRange.is_string()) {
    if (std::sscanf(portRange.as_string().c_str(), "%i-%i", &portFirst, &portLast) != 2)
      throw torrent::input_error("Invalid port_range argument.");
    
//   } else if (portRange.is_list()) {

  } else {
    throw torrent::input_error("Invalid port_range argument.");
  }

  if (portFirst > portLast || portLast >= (1 << 16))
    throw torrent::input_error("Invalid port range.");

  if (rpc::call_command_value("get_port_random")) {
    int boundary = portFirst + random() % (portLast - portFirst + 1);

    if (torrent::connection_manager()->listen_open(boundary, portLast) ||
        torrent::connection_manager()->listen_open(portFirst, boundary))
      return;

  } else {
    if (torrent::connection_manager()->listen_open(portFirst, portLast))
      return;
  }

  throw torrent::input_error("Could not open/bind port for listening: " + std::string(rak::error_number::current().c_str()));
}