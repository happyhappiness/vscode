bool
SocketFd::bind(const rak::socket_address& sa, unsigned int length) {
  check_valid();

  return !::bind(m_fd, sa.c_sockaddr(), length);
}