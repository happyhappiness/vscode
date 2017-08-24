{
    uint_t n = 1;

    /*
     * Note that our use of port_getn() here (and not port_get()) is deliberate:
     * there is a bug in event ports (Sun bug 6456558) whereby a zeroed timeout
     * causes port_get() to return success instead of ETIME when there aren't
     * actually any events (!); by using port_getn() in lieu of port_get(),
     * we can at least workaround the bug by checking for zero returned events
     * and treating it as we would ETIME.
     */
    do {
      memset(&timeout, 0, sizeof timeout);
      r = port_getn(loop->fs_fd, &pe, 1, &n, &timeout);
    }
    while (r == -1 && errno == EINTR);

    if ((r == -1 && errno == ETIME) || n == 0)
      break;

    handle = (uv_fs_event_t*) pe.portev_user;
    assert((r == 0) && "unexpected port_get() error");

    events = 0;
    if (pe.portev_events & (FILE_ATTRIB | FILE_MODIFIED))
      events |= UV_CHANGE;
    if (pe.portev_events & ~(FILE_ATTRIB | FILE_MODIFIED))
      events |= UV_RENAME;
    assert(events != 0);
    handle->fd = PORT_FIRED;
    handle->cb(handle, NULL, events, 0);

    if (handle->fd != PORT_DELETED) {
      r = uv__fs_event_rearm(handle);
      if (r != 0)
        handle->cb(handle, NULL, 0, r);
    }
  }