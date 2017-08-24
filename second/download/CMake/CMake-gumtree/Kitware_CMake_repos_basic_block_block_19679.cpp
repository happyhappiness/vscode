(handle->io_watcher.fd > STDERR_FILENO)
      uv__close(handle->io_watcher.fd)