{
  int err;

  if (alloc_cb == NULL || recv_cb == NULL)
    return -EINVAL;

  if (uv__io_active(&handle->io_watcher, POLLIN))
    return -EALREADY;  /* FIXME(bnoordhuis) Should be -EBUSY. */

  err = uv__udp_maybe_deferred_bind(handle, AF_INET, 0);
  if (err)
    return err;

  handle->alloc_cb = alloc_cb;
  handle->recv_cb = recv_cb;

  uv__io_start(handle->loop, &handle->io_watcher, POLLIN);
  uv__handle_start(handle);

  return 0;
}