(!readable) {
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