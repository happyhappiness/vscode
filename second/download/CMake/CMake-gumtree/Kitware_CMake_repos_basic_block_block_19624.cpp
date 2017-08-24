(i = 0; i < count; i++) {
      /* Already has accepted fd, queue now */
      if (stream->accepted_fd != -1) {
        err = uv__stream_queue_fd(stream, pi[i]);
        if (err != 0) {
          /* Close rest */
          for (; i < count; i++)
            uv__close(pi[i]);
          return err;
        }
      } else {
        stream->accepted_fd = pi[i];
      }
    }