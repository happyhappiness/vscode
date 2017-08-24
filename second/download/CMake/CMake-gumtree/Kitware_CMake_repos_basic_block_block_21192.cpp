{
  CONSOLE_CURSOR_INFO cursor_info;

  if (!GetConsoleCursorInfo(handle->handle, &cursor_info)) {
    *error = GetLastError();
    return -1;
  }

  cursor_info.bVisible = visible;

  if (!SetConsoleCursorInfo(handle->handle, &cursor_info)) {
    *error = GetLastError();
    return -1;
  }

  return 0;
}