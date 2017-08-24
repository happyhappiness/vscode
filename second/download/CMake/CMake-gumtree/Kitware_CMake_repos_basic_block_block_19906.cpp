(type == UV_TTY) {
    /* Reopening a pty in master mode won't work either because the reopened
     * pty will be in slave mode (*BSD) or reopening will allocate a new
     * master/slave pair (Linux). Therefore check if the fd points to a
     * slave device.
     */
    if (uv__tty_is_slave(fd) && ttyname_r(fd, path, sizeof(path)) == 0)
      r = uv__open_cloexec(path, O_RDWR);
    else
      r = -1;

    if (r < 0) {
      /* fallback to using blocking writes */
      if (!readable)
        flags |= UV_STREAM_BLOCKING;
      goto skip;
    }

    newfd = r;

    r = uv__dup2_cloexec(newfd, fd);
    if (r < 0 && r != -EINVAL) {
      /* EINVAL means newfd == fd which could conceivably happen if another
       * thread called close(fd) between our calls to isatty() and open().
       * That's a rather unlikely event but let's handle it anyway.
       */
      uv__close(newfd);
      return r;
    }

    fd = newfd;
  }