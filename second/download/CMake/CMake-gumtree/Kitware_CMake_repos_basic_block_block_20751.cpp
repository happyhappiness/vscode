{
  int err;

  if (process->process_handle == INVALID_HANDLE_VALUE) {
    return UV_EINVAL;
  }

  err = uv__kill(process->process_handle, signum);
  if (err) {
    return err;  /* err is already translated. */
  }

  process->exit_signal = signum;

  return 0;
}