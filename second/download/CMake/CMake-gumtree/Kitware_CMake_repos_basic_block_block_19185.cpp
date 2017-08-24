{
  int err;

  if (loop->inotify_fd != -1)
    return 0;

  err = new_inotify_fd();
  if (err < 0)
    return err;

  loop->inotify_fd = err;
  uv__io_init(&loop->inotify_read_watcher, uv__inotify_read, loop->inotify_fd);
  uv__io_start(loop, &loop->inotify_read_watcher, POLLIN);

  return 0;
}