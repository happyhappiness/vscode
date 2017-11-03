bool
SocketFd::set_reuse_address(bool state) {
  check_valid();
  int opt = state;

  return setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == 0;
}