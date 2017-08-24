(errno == EAGAIN || errno == EWOULDBLOCK) {
        /* Wait for the next one. */
        if (stream->flags & UV_STREAM_READING) {
          uv__io_start(stream->loop, &stream->io_watcher, POLLIN);
          uv__stream_osx_interrupt_select(stream);
        }
        stream->read_cb(stream, 0, &buf);
#if defined(__CYGWIN__) || defined(__MSYS__)
      } else if (errno == ECONNRESET && stream->type == UV_NAMED_PIPE) {
        uv__stream_eof(stream, &buf);
        return;
#endif
      } else {
        /* Error. User should call uv_close(). */
        stream->read_cb(stream, -errno, &buf);
        if (stream->flags & UV_STREAM_READING) {
          stream->flags &= ~UV_STREAM_READING;
          uv__io_stop(stream->loop, &stream->io_watcher, POLLIN);
          if (!uv__io_active(&stream->io_watcher, POLLOUT))
            uv__handle_stop(stream);
          uv__stream_osx_interrupt_select(stream);
        }
      }