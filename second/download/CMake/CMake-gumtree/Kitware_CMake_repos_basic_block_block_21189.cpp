(restore_attributes &&
      (handle->flags & UV_HANDLE_TTY_SAVED_ATTRIBUTES)) {
    if (!GetConsoleScreenBufferInfo(handle->handle, &info)) {
      *error = GetLastError();
      return -1;
    }

    new_attributes = info.wAttributes;
    new_attributes &= ~(FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
    new_attributes |= handle->tty.wr.saved_attributes;

    if (!SetConsoleTextAttribute(handle->handle, new_attributes)) {
      *error = GetLastError();
      return -1;
    }
  }