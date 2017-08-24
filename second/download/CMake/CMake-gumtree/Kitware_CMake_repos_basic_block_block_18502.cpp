{
    pollset_destroy(loop->backend_fd);
    loop->backend_fd = -1;
  }