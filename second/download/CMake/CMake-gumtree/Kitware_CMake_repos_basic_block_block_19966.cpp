(!QUEUE_EMPTY(&handle->write_queue))
      uv__io_start(handle->loop, &handle->io_watcher, POLLOUT)