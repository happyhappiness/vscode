(i = 0; i < nfds; i++)
      if ((int) events[i].data == fd)
        events[i].data = -1