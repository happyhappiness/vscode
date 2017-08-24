{
  int err;

  if (handle->socket != INVALID_SOCKET) {
    err = uv__tcp_keepalive(handle, handle->socket, enable, delay);
    if (err)
      return err;
  }

  if (enable) {
    handle->flags |= UV_HANDLE_TCP_KEEPALIVE;
  } else {
    handle->flags &= ~UV_HANDLE_TCP_KEEPALIVE;
  }

  /* TODO: Store delay if handle->socket isn't created yet. */

  return 0;
}