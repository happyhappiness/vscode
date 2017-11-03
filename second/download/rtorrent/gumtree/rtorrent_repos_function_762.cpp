bool
SocketFd::listen(int size) {
  check_valid();

  return !::listen(m_fd, size);
}