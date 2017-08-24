{
  int pipefd[2];
  int err;

  if (loop->async_io_watcher.fd != -1)
    return 0;

  err = uv__async_eventfd();
  if (err >= 0) {
    pipefd[0] = err;
    pipefd[1] = -1;
  }
  else if (err == -ENOSYS) {
    err = uv__make_pipe(pipefd, UV__F_NONBLOCK);
#if defined(__linux__)
    /* Save a file descriptor by opening one of the pipe descriptors as
     * read/write through the procfs.  That file descriptor can then
     * function as both ends of the pipe.
     */
    if (err == 0) {
      char buf[32];
      int fd;

      snprintf(buf, sizeof(buf), "/proc/self/fd/%d", pipefd[0]);
      fd = uv__open_cloexec(buf, O_RDWR);
      if (fd >= 0) {
        uv__close(pipefd[0]);
        uv__close(pipefd[1]);
        pipefd[0] = fd;
        pipefd[1] = fd;
      }
    }
#endif
  }

  if (err < 0)
    return err;

  uv__io_init(&loop->async_io_watcher, uv__async_io, pipefd[0]);
  uv__io_start(loop, &loop->async_io_watcher, POLLIN);
  loop->async_wfd = pipefd[1];

  return 0;
}