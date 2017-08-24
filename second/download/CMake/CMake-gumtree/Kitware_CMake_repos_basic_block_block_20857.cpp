(handle->tcp.conn.read_buffer.base == NULL ||
        handle->tcp.conn.read_buffer.len == 0) {
      handle->read_cb((uv_stream_t*) handle, UV_ENOBUFS, &handle->tcp.conn.read_buffer);
      return;
    }