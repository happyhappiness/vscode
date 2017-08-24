{
    /* Cancel line-buffered read if not already pending */
    err = uv__cancel_read_console(handle);
    if (err)
      return err;

    handle->flags |= UV_HANDLE_CANCELLATION_PENDING;
  }