(stream->accepted_fd != -1) {
      /* The user hasn't yet accepted called uv_accept() */
      uv__io_stop(loop, &stream->io_watcher, POLLIN);
      return;
    }