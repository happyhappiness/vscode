{
  int err;

  err = uv__signal_loop_once_init(loop);
  if (err)
    return err;

  uv__handle_init(loop, (uv_handle_t*) handle, UV_SIGNAL);
  handle->signum = 0;
  handle->caught_signals = 0;
  handle->dispatched_signals = 0;

  return 0;
}