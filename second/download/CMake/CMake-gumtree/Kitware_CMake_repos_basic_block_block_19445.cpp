(use_fd == -1) {
          uv__write_int(error_fd, -errno);
          _exit(127)