{
    handle->flags &= ~UV_HANDLE_READING;
    handle->loop->active_udp_streams--;
    DECREASE_ACTIVE_COUNT(loop, handle);
  }