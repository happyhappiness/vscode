{
  INPUT_RECORD record;
  DWORD written, err;

  handle->flags &= ~UV_HANDLE_READING;
  DECREASE_ACTIVE_COUNT(handle->loop, handle);

  if (!(handle->flags & UV_HANDLE_READ_PENDING))
    return 0;

  if (handle->flags & UV_HANDLE_TTY_RAW) {
    /* Cancel raw read */
    /* Write some bullshit event to force the console wait to return. */
    memset(&record, 0, sizeof record);
    if (!WriteConsoleInputW(handle->handle, &record, 1, &written)) {
      return GetLastError();
    }
  } else if (!(handle->flags & UV_HANDLE_CANCELLATION_PENDING)) {
    /* Cancel line-buffered read if not already pending */
    err = uv__cancel_read_console(handle);
    if (err)
      return err;

    handle->flags |= UV_HANDLE_CANCELLATION_PENDING;
  }

  return 0;
}