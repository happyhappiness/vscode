{
    handle->flags &= ~UV_HANDLE_ZERO_READ;
    handle->tcp.conn.read_buffer = uv_buf_init(NULL, 0);
    handle->alloc_cb((uv_handle_t*) handle, 65536, &handle->tcp.conn.read_buffer);
    if (handle->tcp.conn.read_buffer.base == NULL ||
        handle->tcp.conn.read_buffer.len == 0) {
      handle->read_cb((uv_stream_t*) handle, UV_ENOBUFS, &handle->tcp.conn.read_buffer);
      return;
    }
    assert(handle->tcp.conn.read_buffer.base != NULL);
    buf = handle->tcp.conn.read_buffer;
  }