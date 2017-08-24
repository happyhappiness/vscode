{
  if (uv__stream_fd(handle) == -1)
    return -EINVAL;

#if defined(__MVS__)
  /* On zOS, backlog=0 has undefined behaviour */
  if (backlog == 0)
    backlog = 1;
  else if (backlog < 0)
    backlog = SOMAXCONN;
#endif

  if (listen(uv__stream_fd(handle), backlog))
    return -errno;

  handle->connection_cb = cb;
  handle->io_watcher.cb = uv__server_io;
  uv__io_start(handle->loop, &handle->io_watcher, POLLIN);
  return 0;
}