void
SocketFd::close() {
  if (::close(m_fd) && errno == EBADF)
    throw torrent::internal_error("SocketFd::close() called on an invalid file descriptor");
}