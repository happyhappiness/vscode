bool
SocketFd::connect(const rak::socket_address& sa) {
  check_valid();

  return !::connect(m_fd, sa.c_sockaddr(), sa.length()) || errno == EINPROGRESS;
}