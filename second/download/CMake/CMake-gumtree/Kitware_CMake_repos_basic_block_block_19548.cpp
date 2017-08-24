{
  uv__stream_select_t* s;
  uv_stream_t* stream;
  int events;

  s = container_of(handle, uv__stream_select_t, async);
  stream = s->stream;

  /* Get and reset stream's events */
  events = s->events;
  ACCESS_ONCE(int, s->events) = 0;

  assert(events != 0);
  assert(events == (events & (POLLIN | POLLOUT)));

  /* Invoke callback on event-loop */
  if ((events & POLLIN) && uv__io_active(&stream->io_watcher, POLLIN))
    uv__stream_io(stream->loop, &stream->io_watcher, POLLIN);

  if ((events & POLLOUT) && uv__io_active(&stream->io_watcher, POLLOUT))
    uv__stream_io(stream->loop, &stream->io_watcher, POLLOUT);

  if (stream->flags & UV_CLOSING)
    return;

  /* NOTE: It is important to do it here, otherwise `select()` might be called
   * before the actual `uv__read()`, leading to the blocking syscall
   */
  uv_sem_post(&s->async_sem);
}