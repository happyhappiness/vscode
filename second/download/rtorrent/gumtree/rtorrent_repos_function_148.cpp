void
apply_d_connection_type(core::Download* download, const std::string& name) {
  torrent::Download::ConnectionType connType;

  if (name == "leech")
    connType = torrent::Download::CONNECTION_LEECH;
  else if (name == "seed")
    connType = torrent::Download::CONNECTION_SEED;
  else
    throw torrent::input_error("Unknown peer connection type selected.");

  download->download()->set_connection_type(connType);
}