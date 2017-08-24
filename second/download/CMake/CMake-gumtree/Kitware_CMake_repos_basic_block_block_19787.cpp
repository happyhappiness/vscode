{
  int err;

  err = uv__nonblock(sock, 1);
  if (err)
    return err;

  return uv__stream_open((uv_stream_t*)handle,
                         sock,
                         UV_STREAM_READABLE | UV_STREAM_WRITABLE);
}