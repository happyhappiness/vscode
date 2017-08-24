{
    /* Terminate on semaphore */
    if (uv_sem_trywait(&s->close_sem) == 0)
      break;

    /* Watch fd using select(2) */
    memset(s->sread, 0, s->sread_sz);
    memset(s->swrite, 0, s->swrite_sz);

    if (uv__io_active(&stream->io_watcher, POLLIN))
      FD_SET(fd, s->sread);
    if (uv__io_active(&stream->io_watcher, POLLOUT))
      FD_SET(fd, s->swrite);
    FD_SET(s->int_fd, s->sread);

    /* Wait indefinitely for fd events */
    r = select(max_fd + 1, s->sread, s->swrite, NULL, NULL);
    if (r == -1) {
      if (errno == EINTR)
        continue;

      /* XXX: Possible?! */
      abort();
    }

    /* Ignore timeouts */
    if (r == 0)
      continue;

    /* Empty socketpair's buffer in case of interruption */
    if (FD_ISSET(s->int_fd, s->sread))
      while (1) {
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

    /* Handle events */
    events = 0;
    if (FD_ISSET(fd, s->sread))
      events |= POLLIN;
    if (FD_ISSET(fd, s->swrite))
      events |= POLLOUT;

    assert(events != 0 || FD_ISSET(s->int_fd, s->sread));
    if (events != 0) {
      ACCESS_ONCE(int, s->events) = events;

      uv_async_send(&s->async);
      uv_sem_wait(&s->async_sem);

      /* Should be processed at this stage */
      assert((s->events == 0) || (stream->flags & UV_CLOSING));
    }
  }