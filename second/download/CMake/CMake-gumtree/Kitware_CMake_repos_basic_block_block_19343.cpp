{
  int err;

  err = uv__nonblock(fd, 1);
  if (err)
    return err;

#if defined(__APPLE__)
  err = uv__stream_try_select((uv_stream_t*) handle, &fd);
  if (err)
    return err;
#endif /* defined(__APPLE__) */

  return uv__stream_open((uv_stream_t*)handle,
                         fd,
                         UV_STREAM_READABLE | UV_STREAM_WRITABLE);
}