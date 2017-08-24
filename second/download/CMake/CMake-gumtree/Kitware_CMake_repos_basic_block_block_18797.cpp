{
    loop->watchers[w->fd] = w;
    loop->nfds++;
  }