(n >= 0) {
      uv_buf_t* buf = &(req->bufs[req->write_index]);
      size_t len = buf->len;

      assert(req->write_index < req->nbufs);

      if ((size_t)n < len) {
        buf->base += n;
        buf->len -= n;
        stream->write_queue_size -= n;
        n = 0;

        /* There is more to write. */
        if (stream->flags & UV_STREAM_BLOCKING) {
          /*
           * If we're blocking then we should not be enabling the write
           * watcher - instead we need to try again.
           */
          goto start;
        } else {
          /* Break loop and ensure the watcher is pending. */
          break;
        }

      } else {
        /* Finished writing the buf at index req->write_index. */
        req->write_index++;

        assert((size_t)n >= len);
        n -= len;

        assert(stream->write_queue_size >= len);
        stream->write_queue_size -= len;

        if (req->write_index == req->nbufs) {
          /* Then we're done! */
          assert(n == 0);
          uv__write_req_finish(req);
          /* TODO: start trying to write the next request. */
          return;
        }
      }
    }