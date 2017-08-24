(loop->async_wfd != loop->async_io_watcher.fd)
      uv__close(loop->async_wfd)