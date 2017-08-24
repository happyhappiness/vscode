{
  loop->backend_fd = kqueue();
  if (loop->backend_fd == -1)
    return -errno;

  uv__cloexec(loop->backend_fd, 1);

  return 0;
}