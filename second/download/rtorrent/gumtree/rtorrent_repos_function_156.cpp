void
SCgi::open_named(const std::string& filename) {
  if (filename.empty() || filename.size() > 4096)
    throw torrent::resource_error("Invalid filename length.");

  char buffer[sizeof(sockaddr_un) + filename.size()];
  sockaddr_un* sa = reinterpret_cast<sockaddr_un*>(buffer);

  sa->sun_family = AF_LOCAL;
  std::memcpy(sa->sun_path, filename.c_str(), filename.size() + 1);

  if (!get_fd().open_local())
    throw torrent::resource_error("Could not open socket for listening.");

  open(sa, offsetof(struct sockaddr_un, sun_path) + filename.size() + 1);
  m_path = filename;
}