{
    err = uv__stream_open((uv_stream_t*)handle,
                          uv__stream_fd(handle),
                          UV_STREAM_READABLE | UV_STREAM_WRITABLE);
  }