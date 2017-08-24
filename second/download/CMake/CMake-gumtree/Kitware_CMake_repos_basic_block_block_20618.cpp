{
  int err;

  if (!(handle->flags & UV_HANDLE_POLL_SLOW)) {
    err = uv__fast_poll_set(handle->loop, handle, events);
  } else {
    err = uv__slow_poll_set(handle->loop, handle, events);
  }

  if (err) {
    return uv_translate_sys_error(err);
  }

  handle->poll_cb = cb;

  return 0;
}