{
  CONSOLE_SCREEN_BUFFER_INFO info;

  if (*error != ERROR_SUCCESS) {
    return -1;
  }

  if (!GetConsoleScreenBufferInfo(handle->handle, &info)) {
    *error = GetLastError();
    return -1;
  }

  uv_tty_update_virtual_window(&info);

  handle->tty.wr.saved_position.X = info.dwCursorPosition.X;
  handle->tty.wr.saved_position.Y = info.dwCursorPosition.Y - uv_tty_virtual_offset;
  handle->flags |= UV_HANDLE_TTY_SAVED_POSITION;

  if (save_attributes) {
    handle->tty.wr.saved_attributes = info.wAttributes &
        (FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
    handle->flags |= UV_HANDLE_TTY_SAVED_ATTRIBUTES;
  }

  return 0;
}