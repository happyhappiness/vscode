(i = 0; i < nfds; i++)
    if ((int) events[i].ident == fd)
      events[i].ident = -1