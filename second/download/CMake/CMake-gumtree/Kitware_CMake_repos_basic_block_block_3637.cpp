{
      pfd[i].fd = socks[i];
      pfd[i].events |= POLLWRNORM|POLLOUT;
    }