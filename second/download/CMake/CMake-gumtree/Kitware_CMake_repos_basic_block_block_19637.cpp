{
          uv__io_start(stream->loop, &stream->io_watcher, POLLIN);
          uv__stream_osx_interrupt_select(stream);
        }