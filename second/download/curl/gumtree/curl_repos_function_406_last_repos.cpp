static void checkFdSet(CURLM *curl, struct Sockets *sockets, fd_set *fdset,
                       int evBitmask, const char *name)
{
  int i;
  for(i = 0; i < sockets->count; ++i) {
    if(FD_ISSET(sockets->sockets[i], fdset)) {
      notifyCurl(curl, sockets->sockets[i], evBitmask, name);
    }
  }
}