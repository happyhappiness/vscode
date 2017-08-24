{
  CONSOLE_SCREEN_BUFFER_INFO info;
  COORD pos;

  if (*error != ERROR_SUCCESS) {
    return -1;
  }

 retry:
  if (!GetConsoleScreenBufferInfo(handle->handle, &info)) {
    *error = GetLastError();
  }

  pos = uv_tty_make_real_coord(handle, &info, x, x_relative, y, y_relative);

  if (!SetConsoleCursorPosition(handle->handle, pos)) {
    if (GetLastError() == ERROR_INVALID_PARAMETER) {
      /* The console may be resized - retry */
      goto retry;
    } else {
      *error = GetLastError();
      return -1;
    }
  }

  return 0;
}