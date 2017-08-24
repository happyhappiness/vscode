{
  uv_loop_t* loop = handle->loop;
  int err;

  if (handle->flags & UV_HANDLE_READING) {
    return WSAEALREADY;
  }

  err = uv_udp_maybe_bind(handle,
                          (const struct sockaddr*) &uv_addr_ip4_any_,
                          sizeof(uv_addr_ip4_any_),
                          0);
  if (err)
    return err;

  handle->flags |= UV_HANDLE_READING;
  INCREASE_ACTIVE_COUNT(loop, handle);
  loop->active_udp_streams++;

  handle->recv_cb = recv_cb;
  handle->alloc_cb = alloc_cb;

  /* If reading was stopped and then started again, there could still be a */
  /* recv request pending. */
  if (!(handle->flags & UV_HANDLE_READ_PENDING))
    uv_udp_queue_recv(loop, handle);

  return 0;
}