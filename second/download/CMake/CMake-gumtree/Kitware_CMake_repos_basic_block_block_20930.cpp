{
      uv_connection_init((uv_stream_t*)handle);
      handle->flags |= UV_HANDLE_READABLE | UV_HANDLE_WRITABLE;
      loop->active_tcp_streams++;
    }