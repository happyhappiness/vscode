(1) {
        r = read(s->int_fd, buf, sizeof(buf));

        if (r == sizeof(buf))
          continue;

        if (r != -1)
          break;

        if (errno == EAGAIN || errno == EWOULDBLOCK)
          break;

        if (errno == EINTR)
          continue;

        abort();
      }