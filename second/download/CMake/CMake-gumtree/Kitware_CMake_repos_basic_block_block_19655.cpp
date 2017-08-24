(error < 0 || QUEUE_EMPTY(&stream->write_queue)) {
    uv__io_stop(stream->loop, &stream->io_watcher, POLLOUT);
  }