std::string
te_client_version(const torrent::PeerInfo* info) {
  char buf[128];
  display::print_client_version(buf, buf + 128, info->client_info());

  return buf;
}