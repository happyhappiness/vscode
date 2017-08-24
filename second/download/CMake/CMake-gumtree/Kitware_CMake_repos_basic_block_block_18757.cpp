{
    rc = -errno;
    if (rc == -EINTR || rc == -EINPROGRESS)
      rc = 0;    /* The close is in progress, not an error. */
    errno = saved_errno;
  }