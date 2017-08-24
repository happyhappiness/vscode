{
    /* The wait handle used for raw reading should be unregistered when the */
    /* wait callback runs. */
    assert(!(handle->flags & UV_HANDLE_TTY_READABLE) ||
           handle->tty.rd.read_raw_wait == NULL);

    assert(!(handle->flags & UV_HANDLE_CLOSED));
    uv__handle_close(handle);
  }