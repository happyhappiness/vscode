void
SCgi::open_port(void* sa, unsigned int length, bool dontRoute) {
  if (!get_fd().open_stream() ||
      (dontRoute && !get_fd().set_dont_route(true)))
    throw torrent::resource_error("Could not open socket for listening: " + std::string(rak::error_number::current().c_str()));

  open(sa, length);
}