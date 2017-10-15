  fstr.write(data, size);
  fstr << std::endl <<"---" << std::endl;
}

void
Manager::handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash) {
  if (!rpc::call_command_value("log.handshake"))
    return;
  
  std::string peer;
  std::string download;

  const rak::socket_address* socketAddress = rak::socket_address::cast_from(sa);
