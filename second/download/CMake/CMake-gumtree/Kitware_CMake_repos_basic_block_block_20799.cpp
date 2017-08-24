{
  if (handle->type != UV_NAMED_PIPE)
    return UV_EINVAL;

  if (blocking != 0)
    handle->flags |= UV_HANDLE_BLOCKING_WRITES;
  else
    handle->flags &= ~UV_HANDLE_BLOCKING_WRITES;

  return 0;
}