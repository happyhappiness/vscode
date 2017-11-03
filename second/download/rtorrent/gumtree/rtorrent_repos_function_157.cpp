void
SCgi::open(void* sa, unsigned int length) {
  try {
    if (!get_fd().set_nonblock() ||
        !get_fd().set_reuse_address(true) ||
        !get_fd().bind(*reinterpret_cast<rak::socket_address*>(sa), length) ||
        !get_fd().listen(max_tasks))
      throw torrent::resource_error("Could not prepare socket for listening: " + std::string(rak::error_number::current().c_str()));

    torrent::connection_manager()->inc_socket_count();

    control->poll()->open(this);
    control->poll()->insert_read(this);
    control->poll()->insert_error(this);

  } catch (torrent::resource_error& e) {
    get_fd().close();
    get_fd().clear();

    throw e;
  }
}