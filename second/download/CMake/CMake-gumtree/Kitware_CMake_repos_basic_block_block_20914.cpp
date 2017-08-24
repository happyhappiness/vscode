(req->u.io.overlapped.InternalHigh > 0) {
        /* Successful read */
        handle->read_cb((uv_stream_t*)handle,
                        req->u.io.overlapped.InternalHigh,
                        &handle->tcp.conn.read_buffer);
        /* Read again only if bytes == buf.len */
        if (req->u.io.overlapped.InternalHigh < handle->tcp.conn.read_buffer.len) {
          goto done;
        }
      } else {
        /* Connection closed */
        if (handle->flags & UV_HANDLE_READING) {
          handle->flags &= ~UV_HANDLE_READING;
          DECREASE_ACTIVE_COUNT(loop, handle);
        }
        handle->flags &= ~UV_HANDLE_READABLE;

        buf.base = 0;
        buf.len = 0;
        handle->read_cb((uv_stream_t*)handle, UV_EOF, &handle->tcp.conn.read_buffer);
        goto done;
      }