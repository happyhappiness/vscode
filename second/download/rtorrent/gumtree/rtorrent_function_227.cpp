std::string
ClientInfo::str(const char* id) const {
  char buf[128];
  print(buf, buf + 127, id);

  return std::string(buf);
}