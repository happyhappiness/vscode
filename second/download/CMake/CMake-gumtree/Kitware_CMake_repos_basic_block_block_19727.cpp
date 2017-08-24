{
  int portfd;
  int first_run;
  int err;

  if (uv__is_active(handle))
    return -EINVAL;

  first_run = 0;
  if (handle->loop->fs_fd == -1) {
    portfd = port_create();
    if (portfd == -1)
      return -errno;
    handle->loop->fs_fd = portfd;
    first_run = 1;
  }

  uv__handle_start(handle);
  handle->path = uv__strdup(path);
  handle->fd = PORT_UNUSED;
  handle->cb = cb;

  memset(&handle->fo, 0, sizeof handle->fo);
  handle->fo.fo_name = handle->path;
  err = uv__fs_event_rearm(handle);
  if (err != 0) {
    uv_fs_event_stop(handle);
    return err;
  }

  if (first_run) {
    uv__io_init(&handle->loop->fs_event_watcher, uv__fs_event_read, portfd);
    uv__io_start(handle->loop, &handle->loop->fs_event_watcher, POLLIN);
  }

  return 0;
}