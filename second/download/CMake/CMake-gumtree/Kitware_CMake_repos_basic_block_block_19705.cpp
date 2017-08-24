(errno == EINTR || errno == ETIME)
        saved_errno = errno;
      else
        abort()