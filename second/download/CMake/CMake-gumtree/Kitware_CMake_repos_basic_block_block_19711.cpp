{
    q = QUEUE_HEAD(&loop->watcher_queue);
    QUEUE_REMOVE(q);
    QUEUE_INIT(q);

    w = QUEUE_DATA(q, uv__io_t, watcher_queue);
    assert(w->pevents != 0);

    if (port_associate(loop->backend_fd, PORT_SOURCE_FD, w->fd, w->pevents, 0))
      abort();

    w->events = w->pevents;
  }