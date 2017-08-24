{
    assert(!(handle->flags & UV_HANDLE_CLOSED));
    uv__handle_close(handle);
  }