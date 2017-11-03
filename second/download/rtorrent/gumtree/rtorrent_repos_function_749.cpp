bool
SocketFd::set_priority(priority_type p) {
  check_valid();
  int opt = p;

  return setsockopt(m_fd, IPPROTO_IP, IP_TOS, &opt, sizeof(opt)) == 0;
}