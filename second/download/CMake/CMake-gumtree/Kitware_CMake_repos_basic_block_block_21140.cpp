(!SetConsoleCursorPosition(handle->handle, origin)) {
    *error = GetLastError();
    return -1;
  }