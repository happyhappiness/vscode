{
  int err;
  int fd;

  loop->fs_fd = -1;
  loop->backend_fd = -1;

  fd = port_create();
  if (fd == -1)
    return -errno;

  err = uv__cloexec(fd, 1);
  if (err) {
    uv__close(fd);
    return err;
  }
  loop->backend_fd = fd;

  return 0;
}