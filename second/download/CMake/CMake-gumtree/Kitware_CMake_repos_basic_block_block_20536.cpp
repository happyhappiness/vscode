{
    /* Initialize and optionally start the eof timer. Only do this if the */
    /* pipe is readable and we haven't seen EOF come in ourselves. */
    eof_timer_init(handle);

    /* If reading start the timer right now. */
    /* Otherwise uv_pipe_queue_read will start it. */
    if (handle->flags & UV_HANDLE_READ_PENDING) {
      eof_timer_start(handle);
    }

  }