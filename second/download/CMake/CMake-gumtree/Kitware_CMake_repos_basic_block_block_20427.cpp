{
    handle->flags &= ~UV_HANDLE_WRITABLE;
    eof_timer_destroy(handle);
  }