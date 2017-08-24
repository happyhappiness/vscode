(nwritten = 0; nwritten < nread; ) {
      do
        n = write(out_fd, buf + nwritten, nread - nwritten);
      while (n == -1 && errno == EINTR);

      if (n != -1) {
        nwritten += n;
        continue;
      }

      if (errno != EAGAIN && errno != EWOULDBLOCK) {
        nsent = -1;
        goto out;
      }

      pfd.fd = out_fd;
      pfd.events = POLLOUT;
      pfd.revents = 0;

      do
        n = poll(&pfd, 1, -1);
      while (n == -1 && errno == EINTR);

      if (n == -1 || (pfd.revents & ~POLLOUT) != 0) {
        errno = EIO;
        nsent = -1;
        goto out;
      }
    }