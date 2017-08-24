static void uv__process_child_init(const uv_process_options_t* options,
                                   int stdio_count,
                                   int (*pipes)[2],
                                   int error_fd) {
  int close_fd;
  int use_fd;
  int fd;

  if (options->flags & UV_PROCESS_DETACHED)
    setsid();

  /* First duplicate low numbered fds, since it's not safe to duplicate them,
   * they could get replaced. Example: swapping stdout and stderr; without
   * this fd 2 (stderr) would be duplicated into fd 1, thus making both
   * stdout and stderr go to the same fd, which was not the intention. */
  for (fd = 0; fd < stdio_count; fd++) {
    use_fd = pipes[fd][1];
    if (use_fd < 0 || use_fd >= fd)
      continue;
    pipes[fd][1] = fcntl(use_fd, F_DUPFD, stdio_count);
    if (pipes[fd][1] == -1) {
      uv__write_int(error_fd, -errno);
      _exit(127);
    }
  }

  for (fd = 0; fd < stdio_count; fd++) {
    close_fd = pipes[fd][0];
    use_fd = pipes[fd][1];

    if (use_fd < 0) {
      if (fd >= 3)
        continue;
      else {
        /* redirect stdin, stdout and stderr to /dev/null even if UV_IGNORE is
         * set
         */
        use_fd = open("/dev/null", fd == 0 ? O_RDONLY : O_RDWR);
        close_fd = use_fd;

        if (use_fd == -1) {
          uv__write_int(error_fd, -errno);
          _exit(127)