{
      pfd[i].fd = socks[i];
      pfd[i].events |= POLLRDNORM|POLLIN;
    }