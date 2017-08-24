{
  uv__stream_queued_fds_t* queued_fds;

  if (!handle->ipc)
    return 0;

  if (handle->accepted_fd == -1)
    return 0;

  if (handle->queued_fds == NULL)
    return 1;

  queued_fds = handle->queued_fds;
  return queued_fds->offset + 1;
}