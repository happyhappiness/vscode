(handle->loop->fs_fd == -1) {
    portfd = port_create();
    if (portfd == -1)
      return -errno;
    handle->loop->fs_fd = portfd;
    first_run = 1;
  }