(handle->flags & UV_HANDLE_CONNECTION ||
      handle->handle != INVALID_HANDLE_VALUE) {
    *size = 0;
    return 0;
  }