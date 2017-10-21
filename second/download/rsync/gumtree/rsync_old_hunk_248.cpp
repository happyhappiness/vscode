
    if (ret == 0) return total;

    if (ret == -1 && !(errno == EWOULDBLOCK || errno == EAGAIN)) 
      return -1;

    if (ret == -1) {
      read_check(buffer_f_in);

      FD_ZERO(&fds);
      FD_SET(fd,&fds);
      tv.tv_sec = BLOCKING_TIMEOUT;
      tv.tv_usec = 0;
      select(fd+1,NULL,&fds,NULL,&tv);
    } else {
      total += ret;
    }
  }

  return total;
