(w == NULL) {
        /* File descriptor that we've stopped watching, disarm it. */
        /* TODO batch up */
        struct kevent events[1];

        EV_SET(events + 0, fd, ev->filter, EV_DELETE, 0, 0, 0);
        if (kevent(loop->backend_fd, events, 1, NULL, 0, NULL))
          if (errno != EBADF && errno != ENOENT)
            abort();

        continue;
      }