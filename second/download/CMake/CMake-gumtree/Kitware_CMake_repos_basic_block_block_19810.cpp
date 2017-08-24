{
  int err;

  if (uv__stream_fd(handle) != -1) {
    err =uv__tcp_keepalive(uv__stream_fd(handle), on, delay);
    if (err)
      return err;
  }

  if (on)
    handle->flags |= UV_TCP_KEEPALIVE;
  else
    handle->flags &= ~UV_TCP_KEEPALIVE;

  /* TODO Store delay if uv__stream_fd(handle) == -1 but don't want to enlarge
   *      uv_tcp_t with an int that's almost never used...
   */

  return 0;
}