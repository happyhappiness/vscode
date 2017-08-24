((handle->flags & UV_HANDLE_READING) ||
        !(handle->flags & UV_HANDLE_ZERO_READ)) {
      handle->flags &= ~UV_HANDLE_READING;
      DECREASE_ACTIVE_COUNT(loop, handle);
      buf = (handle->flags & UV_HANDLE_ZERO_READ) ?
            uv_buf_init(NULL, 0) : handle->tcp.conn.read_buffer;

      err = GET_REQ_SOCK_ERROR(req);

      if (err == WSAECONNABORTED) {
        /*
         * Turn WSAECONNABORTED into UV_ECONNRESET to be consistent with Unix.
         */
        err = WSAECONNRESET;
      }

      handle->read_cb((uv_stream_t*)handle,
                      uv_translate_sys_error(err),
                      &buf);
    }