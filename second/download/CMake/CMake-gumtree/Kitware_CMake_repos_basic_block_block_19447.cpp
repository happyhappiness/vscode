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