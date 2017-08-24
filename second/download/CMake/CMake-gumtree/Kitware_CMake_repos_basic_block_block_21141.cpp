(!SetConsoleTextAttribute(handle->handle, char_attrs)) {
    *error = GetLastError();
    return -1;
  }