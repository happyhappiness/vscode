{
  if (port_associate(loop->backend_fd, PORT_SOURCE_FD, fd, POLLIN, 0))
    return -errno;

  if (port_dissociate(loop->backend_fd, PORT_SOURCE_FD, fd))
    abort();

  return 0;
}