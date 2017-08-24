{
    handle->tty.wr.saved_attributes = info.wAttributes &
        (FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
    handle->flags |= UV_HANDLE_TTY_SAVED_ATTRIBUTES;
  }