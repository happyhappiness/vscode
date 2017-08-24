(i = 0; i < nfds; i++)
      if ((int) events[i].fd == fd)
        events[i].fd = -1