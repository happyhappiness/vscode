{
        /* Successful read */
        handle->read_cb((uv_stream_t*)handle,
                        req->u.io.overlapped.InternalHigh,
                        &handle->tcp.conn.read_buffer);
        /* Read again only if bytes == buf.len */
        if (req->u.io.overlapped.InternalHigh < handle->tcp.conn.read_buffer.len) {
          goto done;
        }
      }