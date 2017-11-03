const char*
retrieve_d_connection_type(core::Download* download) {
  switch (download->download()->connection_type()) {
  case torrent::Download::CONNECTION_LEECH:
    return "leech";
  case torrent::Download::CONNECTION_SEED:
    return "seed";
  default:
    return "unknown";
  }
}