(handle->flags & UV_HANDLE_TTY_SAVED_POSITION) {
    if (uv_tty_move_caret(handle,
                          handle->tty.wr.saved_position.X,
                          0,
                          handle->tty.wr.saved_position.Y,
                          0,
                          error) != 0) {
      return -1;
    }
  }