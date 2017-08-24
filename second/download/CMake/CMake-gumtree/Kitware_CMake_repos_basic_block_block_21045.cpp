{
  HANDLE handle;
  CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

  handle = (HANDLE) uv__get_osfhandle(fd);
  if (handle == INVALID_HANDLE_VALUE)
    return UV_EBADF;

  if (fd <= 2) {
    /* In order to avoid closing a stdio file descriptor 0-2, duplicate the
     * underlying OS handle and forget about the original fd.
     * We could also opt to use the original OS handle and just never close it,
     * but then there would be no reliable way to cancel pending read operations
     * upon close.
     */
    if (!DuplicateHandle(INVALID_HANDLE_VALUE,
                         handle,
                         INVALID_HANDLE_VALUE,
                         &handle,
                         0,
                         FALSE,
                         DUPLICATE_SAME_ACCESS))
      return uv_translate_sys_error(GetLastError());
    fd = -1;
  }

  if (!readable) {
    /* Obtain the screen buffer info with the output handle. */
    if (!GetConsoleScreenBufferInfo(handle, &screen_buffer_info)) {
      return uv_translate_sys_error(GetLastError());
    }

    /* Obtain the the tty_output_lock because the virtual window state is */
    /* shared between all uv_tty_t handles. */
    uv_sem_wait(&uv_tty_output_lock);

    if (uv__vterm_state == UV_UNCHECKED)
      uv__determine_vterm_state(handle);

    /* Store the global tty output handle. This handle is used by TTY read */
    /* streams to update the virtual window when a CONSOLE_BUFFER_SIZE_EVENT */
    /* is received. */
    uv_tty_output_handle = handle;

    /* Remember the original console text attributes. */
    uv_tty_capture_initial_style(&screen_buffer_info);

    uv_tty_update_virtual_window(&screen_buffer_info);

    uv_sem_post(&uv_tty_output_lock);
  }


  uv_stream_init(loop, (uv_stream_t*) tty, UV_TTY);
  uv_connection_init((uv_stream_t*) tty);

  tty->handle = handle;
  tty->u.fd = fd;
  tty->reqs_pending = 0;
  tty->flags |= UV_HANDLE_BOUND;

  if (readable) {
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
  } else {
    /* TTY output specific fields. */
    tty->flags |= UV_HANDLE_WRITABLE;

    /* Init utf8-to-utf16 conversion state. */
    tty->tty.wr.utf8_bytes_left = 0;
    tty->tty.wr.utf8_codepoint = 0;

    /* Initialize eol conversion state */
    tty->tty.wr.previous_eol = 0;

    /* Init ANSI parser state. */
    tty->tty.wr.ansi_parser_state = ANSI_NORMAL;
  }

  return 0;
}