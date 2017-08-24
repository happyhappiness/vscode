(!(handle->flags & UV_HANDLE_BOUND)) {
    err = uv_tcp_try_bind(handle,
                          (const struct sockaddr*) &uv_addr_ip4_any_,
                          sizeof(uv_addr_ip4_any_),
                          0);
    if (err)
      return err;
    if (handle->delayed_error)
      return handle->delayed_error;
  }