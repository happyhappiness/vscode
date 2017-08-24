{
        /* File descriptor that we've stopped watching, disarm it.
         *
         * Ignore all errors because we may be racing with another thread
         * when the file descriptor is closed.
         */
        epoll_ctl(loop->ep, UV__EPOLL_CTL_DEL, fd, pe);
        continue;
      }