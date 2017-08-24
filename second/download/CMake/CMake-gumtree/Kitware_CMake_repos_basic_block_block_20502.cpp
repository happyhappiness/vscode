(send_handle && ((send_handle->type != UV_TCP) ||
      (!(send_handle->flags & UV_HANDLE_BOUND) &&
       !(send_handle->flags & UV_HANDLE_CONNECTION)))) {
    return ERROR_NOT_SUPPORTED;
  }