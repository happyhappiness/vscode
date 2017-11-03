bool
SocketFd::set_dont_route(bool state) {
  check_valid();
  int opt = state;

  return setsockopt(m_fd, SOL_SOCKET, SO_DONTROUTE, &opt, sizeof(opt)) == 0;
}