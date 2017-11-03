bool
SocketFd::bind(const rak::socket_address& sa) {
  check_valid();

  return !::bind(m_fd, sa.c_sockaddr(), sa.length());
}