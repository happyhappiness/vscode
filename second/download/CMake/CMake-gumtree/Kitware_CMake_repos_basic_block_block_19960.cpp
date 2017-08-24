(flags & UV_UDP_REUSEADDR) {
    err = uv__set_reuse(fd);
    if (err)
      return err;
  }