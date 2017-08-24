{
  if (handle->fd == -1)
    return -EBADF;

  if (port_associate(handle->loop->fs_fd,
                     PORT_SOURCE_FILE,
                     (uintptr_t) &handle->fo,
                     FILE_ATTRIB | FILE_MODIFIED,
                     handle) == -1) {
    return -errno;
  }
  handle->fd = PORT_LOADED;

  return 0;
}