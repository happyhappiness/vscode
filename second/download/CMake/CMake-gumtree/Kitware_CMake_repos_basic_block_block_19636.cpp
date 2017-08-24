{
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