(ReadFile(handle->handle,
                   buf.base,
                   min(buf.len, avail),
                   &bytes,
                   NULL)) {
        /* Successful read */
        if (handle->ipc) {
          assert(handle->pipe.conn.remaining_ipc_rawdata_bytes >= bytes);
          handle->pipe.conn.remaining_ipc_rawdata_bytes =
            handle->pipe.conn.remaining_ipc_rawdata_bytes - bytes;
        }
        handle->read_cb((uv_stream_t*)handle, bytes, &buf);

        /* Read again only if bytes == buf.len */
        if (bytes <= buf.len) {
          break;
        }
      } else {
        uv_pipe_read_error_or_eof(loop, handle, GetLastError(), buf);
        break;
      }