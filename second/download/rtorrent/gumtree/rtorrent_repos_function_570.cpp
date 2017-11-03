void
Manager::handshake_log(const sockaddr* sa, int msg, int err, const torrent::HashString* hash) {
  if (!rpc::call_command_value("get_handshake_log"))
    return;
  
  std::string peer;
  std::string download;

  const rak::socket_address* socketAddress = rak::socket_address::cast_from(sa);

  if (socketAddress->is_valid()) {
    char port[6];
    snprintf(port, sizeof(port), "%d", socketAddress->port());
    peer = socketAddress->address_str() + ":" + port;
  } else {
    peer = "(unknown)";
  }

//   torrent::Download d = torrent::download_find(hash);

//   if (d.is_valid())
//     download = ": " + d.name();
//   else
    download = "";

  switch (msg) {
  case torrent::ConnectionManager::handshake_incoming:
    m_logComplete.push_front("Incoming connection from " + peer + download);
    break;
  case torrent::ConnectionManager::handshake_outgoing:
    m_logComplete.push_front("Outgoing connection to " + peer + download);
    break;
  case torrent::ConnectionManager::handshake_outgoing_encrypted:
    m_logComplete.push_front("Outgoing encrypted connection to " + peer + download);
    break;
  case torrent::ConnectionManager::handshake_outgoing_proxy:
    m_logComplete.push_front("Outgoing proxy connection to " + peer + download);
    break;
  case torrent::ConnectionManager::handshake_success:
    m_logComplete.push_front("Successful handshake: " + peer + download);
    break;
  case torrent::ConnectionManager::handshake_dropped:
    m_logComplete.push_front("Dropped handshake: " + peer + " - " + torrent::strerror(err) + download);
    break;
  case torrent::ConnectionManager::handshake_failed:
    m_logComplete.push_front("Handshake failed: " + peer + " - " + torrent::strerror(err) + download);
    break;
  case torrent::ConnectionManager::handshake_retry_plaintext:
    m_logComplete.push_front("Trying again without encryption: " + peer + download);
    break;
  case torrent::ConnectionManager::handshake_retry_encrypted:
    m_logComplete.push_front("Trying again encrypted: " + peer + download);
    break;
  default:
    m_logComplete.push_front("Unknown handshake message for " + peer + download);
    break;
  }
}