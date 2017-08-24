{
  const struct sockaddr* bind_addr;
  int err;

  if (!(handle->flags & UV_HANDLE_BOUND)) {
    if (addrlen == sizeof(uv_addr_ip4_any_)) {
      bind_addr = (const struct sockaddr*) &uv_addr_ip4_any_;
    } else if (addrlen == sizeof(uv_addr_ip6_any_)) {
      bind_addr = (const struct sockaddr*) &uv_addr_ip6_any_;
    } else {
      abort();
    }
    err = uv_udp_maybe_bind(handle, bind_addr, addrlen, 0);
    if (err)
      return uv_translate_sys_error(err);
  }

  err = uv__send(req, handle, bufs, nbufs, addr, addrlen, send_cb);
  if (err)
    return uv_translate_sys_error(err);

  return 0;
}