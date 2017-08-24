{
    uv__io_init(&handle->loop->fs_event_watcher, uv__fs_event_read, portfd);
    uv__io_start(handle->loop, &handle->loop->fs_event_watcher, POLLIN);
  }