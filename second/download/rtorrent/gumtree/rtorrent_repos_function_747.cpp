inline void
SocketFd::check_valid() const {
  if (!is_valid())
    throw torrent::internal_error("SocketFd function called on an invalid fd.");
}