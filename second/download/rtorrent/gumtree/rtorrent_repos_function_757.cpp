bool
SocketFd::open_local() {
  return (m_fd = socket(PF_LOCAL, SOCK_DGRAM, 0)) != -1;
}