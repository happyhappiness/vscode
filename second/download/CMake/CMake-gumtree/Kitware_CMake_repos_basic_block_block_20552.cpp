{
    /* "\\\\.\\pipe" + name */
    *size = pipe_prefix_len + addrlen + 1;
    err = UV_ENOBUFS;
    goto error;
  }