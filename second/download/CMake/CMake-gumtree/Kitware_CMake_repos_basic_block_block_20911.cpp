{
      buf = uv_buf_init(NULL, 0);
      handle->alloc_cb((uv_handle_t*) handle, 65536, &buf);
      if (buf.base == NULL || buf.len == 0) {
        handle->read_cb((uv_stream_t*) handle, UV_ENOBUFS, &buf);
        break;
      }
      assert(buf.base != NULL);

      flags = 0;
      if (WSARecv(handle->socket,
                  (WSABUF*)&buf,
                  1,
                  &bytes,
                  &flags,
                  NULL,
                  NULL) != SOCKET_ERROR) {
        if (bytes > 0) {
          /* Successful read */
          handle->read_cb((uv_stream_t*)handle, bytes, &buf);
          /* Read again only if bytes == buf.len */
          if (bytes < buf.len) {
            break;
          }
        } else {
          /* Connection closed */
          handle->flags &= ~(UV_HANDLE_READING | UV_HANDLE_READABLE);
          DECREASE_ACTIVE_COUNT(loop, handle);

          handle->read_cb((uv_stream_t*)handle, UV_EOF, &buf);
          break;
        }
      } else {
        err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
          /* Read buffer was completely empty, report a 0-byte read. */
          handle->read_cb((uv_stream_t*)handle, 0, &buf);
        } else {
          /* Ouch! serious error. */
          handle->flags &= ~UV_HANDLE_READING;
          DECREASE_ACTIVE_COUNT(loop, handle);

          if (err == WSAECONNABORTED) {
            /* Turn WSAECONNABORTED into UV_ECONNRESET to be consistent with */
            /* Unix. */
            err = WSAECONNRESET;
          }

          handle->read_cb((uv_stream_t*)handle,
                          uv_translate_sys_error(err),
                          &buf);
        }
        break;
      }
    }