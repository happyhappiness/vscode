{
      /* Error */
      req->error = -errno;
      uv__write_req_finish(req);
      uv__io_stop(stream->loop, &stream->io_watcher, POLLOUT);
      if (!uv__io_active(&stream->io_watcher, POLLIN))
        uv__handle_stop(stream);
      uv__stream_osx_interrupt_select(stream);
      return;
    }