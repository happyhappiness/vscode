bool
SocketFd::open_datagram() {
  return (m_fd = socket(PF_INET, SOCK_DGRAM, 0)) != -1;
}