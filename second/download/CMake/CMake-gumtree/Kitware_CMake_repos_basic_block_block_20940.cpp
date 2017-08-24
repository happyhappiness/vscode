{
    err = uv__tcp_keepalive(handle, handle->socket, enable, delay);
    if (err)
      return err;
  }