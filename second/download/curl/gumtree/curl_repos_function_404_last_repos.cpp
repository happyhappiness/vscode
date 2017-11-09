static void updateFdSet(struct Sockets* sockets, fd_set* fdset,
                        curl_socket_t *maxFd)
{
  int i;
  for(i = 0; i < sockets->count; ++i) {
    FD_SET(sockets->sockets[i], fdset);
    if(*maxFd < sockets->sockets[i] + 1) {
      *maxFd = sockets->sockets[i] + 1;
    }
  }
}