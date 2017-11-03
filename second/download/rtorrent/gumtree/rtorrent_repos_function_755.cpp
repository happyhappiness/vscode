bool
SocketFd::open_stream() {
  return (m_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1;
}