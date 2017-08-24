(kevent(loop->backend_fd, events, 1, NULL, 0, NULL))
          if (errno != EBADF && errno != ENOENT)
            abort()