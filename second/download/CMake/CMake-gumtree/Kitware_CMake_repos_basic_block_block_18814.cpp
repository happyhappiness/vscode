(len >= *size) {
    *size = len + 1;
    uv_os_free_passwd(&pwd);
    return -ENOBUFS;
  }