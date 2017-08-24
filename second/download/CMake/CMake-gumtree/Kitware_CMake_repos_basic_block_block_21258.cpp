(family == AF_INET6) {
    handle->flags |= UV_HANDLE_IPV6;
  } else {
    assert(!(handle->flags & UV_HANDLE_IPV6));
  }