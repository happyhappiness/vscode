(handle->flags & UV_HANDLE_TCP_KEEPALIVE) {
    err = uv__tcp_keepalive(handle, socket, 1, 60);
    if (err)
      return err;
  }