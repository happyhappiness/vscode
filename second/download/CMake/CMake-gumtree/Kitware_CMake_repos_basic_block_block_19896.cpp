{
    int rc = r;
    if (newfd != -1)
      uv__close(newfd);
    QUEUE_REMOVE(&tty->handle_queue);
    do
      r = fcntl(fd, F_SETFL, saved_flags);
    while (r == -1 && errno == EINTR);
    return rc;
  }