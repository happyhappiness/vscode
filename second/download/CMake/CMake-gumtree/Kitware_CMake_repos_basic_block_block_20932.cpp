{
    uv_connection_init((uv_stream_t*)tcp);
    tcp->flags |= UV_HANDLE_READABLE | UV_HANDLE_WRITABLE;
  }