bool
SocketFd::set_nonblock() {
  check_valid();

  return fcntl(m_fd, F_SETFL, O_NONBLOCK) == 0;
}