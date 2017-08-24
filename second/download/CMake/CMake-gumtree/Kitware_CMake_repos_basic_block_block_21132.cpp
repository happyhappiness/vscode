(!WriteConsoleW(handle->handle,
                     (void*) buffer,
                     length,
                     &written,
                     NULL)) {
    *error = GetLastError();
    return -1;
  }