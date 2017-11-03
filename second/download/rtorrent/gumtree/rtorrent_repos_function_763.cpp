SocketFd
SocketFd::accept(rak::socket_address* sa) {
  check_valid();
  socklen_t len = sizeof(rak::socket_address);

  return SocketFd(::accept(m_fd, sa != NULL ? sa->c_sockaddr() : NULL, &len));
}