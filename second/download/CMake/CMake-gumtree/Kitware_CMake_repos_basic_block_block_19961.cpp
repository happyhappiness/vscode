(fd == -1) {
    err = uv__socket(addr->sa_family, SOCK_DGRAM, 0);
    if (err < 0)
      return err;
    fd = err;
    handle->io_watcher.fd = fd;
  }