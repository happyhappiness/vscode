(on)
    handle->flags |= UV_TCP_NODELAY;
  else
    handle->flags &= ~UV_TCP_NODELAY