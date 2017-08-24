{
    /* Initialize TTY input specific fields. */
    tty->flags |= UV_HANDLE_TTY_READABLE | UV_HANDLE_READABLE;
    /* TODO: remove me in v2.x. */
    tty->tty.rd.unused_ = NULL;
    tty->tty.rd.read_line_buffer = uv_null_buf_;
    tty->tty.rd.read_raw_wait = NULL;

    /* Init keycode-to-vt100 mapper state. */
    tty->tty.rd.last_key_len = 0;
    tty->tty.rd.last_key_offset = 0;
    tty->tty.rd.last_utf16_high_surrogate = 0;
    memset(&tty->tty.rd.last_input_record, 0, sizeof tty->tty.rd.last_input_record);
  }