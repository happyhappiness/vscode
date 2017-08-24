{
  DWORD written;

  if (*error != ERROR_SUCCESS) {
    return -1;
  }

  if (!WriteConsoleW(handle->handle,
                     (void*) buffer,
                     length,
                     &written,
                     NULL)) {
    *error = GetLastError();
    return -1;
  }

  return 0;
}