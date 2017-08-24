{
  DWORD flags;
  unsigned char was_reading;
  uv_alloc_cb alloc_cb;
  uv_read_cb read_cb;
  int err;

  if (!(tty->flags & UV_HANDLE_TTY_READABLE)) {
    return UV_EINVAL;
  }

  if (!!mode == !!(tty->flags & UV_HANDLE_TTY_RAW)) {
    return 0;
  }

  switch (mode) {
    case UV_TTY_MODE_NORMAL:
      flags = ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT;
      break;
    case UV_TTY_MODE_RAW:
      flags = ENABLE_WINDOW_INPUT;
      break;
    case UV_TTY_MODE_IO:
      return UV_ENOTSUP;
    default:
      return UV_EINVAL;
  }

  /* If currently reading, stop, and restart reading. */
  if (tty->flags & UV_HANDLE_READING) {
    was_reading = 1;
    alloc_cb = tty->alloc_cb;
    read_cb = tty->read_cb;
    err = uv_tty_read_stop(tty);
    if (err) {
      return uv_translate_sys_error(err);
    }
  } else {
    was_reading = 0;
  }

  uv_sem_wait(&uv_tty_output_lock);
  if (!SetConsoleMode(tty->handle, flags)) {
    err = uv_translate_sys_error(GetLastError());
    uv_sem_post(&uv_tty_output_lock);
    return err;
  }
  uv_sem_post(&uv_tty_output_lock);

  /* Update flag. */
  tty->flags &= ~UV_HANDLE_TTY_RAW;
  tty->flags |= mode ? UV_HANDLE_TTY_RAW : 0;

  /* If we just stopped reading, restart. */
  if (was_reading) {
    err = uv_tty_read_start(tty, alloc_cb, read_cb);
    if (err) {
      return uv_translate_sys_error(err);
    }
  }

  return 0;
}