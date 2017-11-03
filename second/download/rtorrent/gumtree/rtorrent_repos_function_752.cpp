bool
SocketFd::set_send_buffer_size(uint32_t s) {
  check_valid();
  int opt = s;

  return setsockopt(m_fd, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt)) == 0;
}