uint32_t
Download::priority() {
  return bencode()->get_key("rtorrent").get_key_value("priority");
}