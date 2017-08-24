(kevent(loop->backend_fd, events, 1, NULL, 0, NULL))
            if (errno != ENOENT)
              abort()