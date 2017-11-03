int
SocketFd::get_error() const {
  check_valid();

  int err;
  socklen_t length = sizeof(err);

  if (getsockopt(m_fd, SOL_SOCKET, SO_ERROR, &err, &length) == -1)
    throw torrent::internal_error("SocketFd::get_error() could not get error");

  return err;
}