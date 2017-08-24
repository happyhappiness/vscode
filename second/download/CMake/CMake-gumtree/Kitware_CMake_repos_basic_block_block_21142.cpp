(!GetConsoleScreenBufferInfo(handle->handle, &info)) {
    *error = GetLastError();
    return -1;
  }