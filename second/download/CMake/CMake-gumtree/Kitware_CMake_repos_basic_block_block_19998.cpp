{
  if (setsockopt(handle->io_watcher.fd,
                 SOL_SOCKET,
                 SO_BROADCAST,
                 &on,
                 sizeof(on))) {
    return -errno;
  }

  return 0;
}