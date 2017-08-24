{
  uv_loop_t* loop = handle->loop;

  if (!(handle->flags & UV_HANDLE_TTY_READABLE)) {
    return ERROR_INVALID_PARAMETER;
  }

  handle->flags |= UV_HANDLE_READING;
  INCREASE_ACTIVE_COUNT(loop, handle);
  handle->read_cb = read_cb;
  handle->alloc_cb = alloc_cb;

  /* If reading was stopped and then started again, there could still be a */
  /* read request pending. */
  if (handle->flags & UV_HANDLE_READ_PENDING) {
    return 0;
  }

  /* Maybe the user stopped reading half-way while processing key events. */
  /* Short-circuit if this could be the case. */
  if (handle->tty.rd.last_key_len > 0) {
    SET_REQ_SUCCESS(&handle->read_req);
    uv_insert_pending_req(handle->loop, (uv_req_t*) &handle->read_req);
    /* Make sure no attempt is made to insert it again until it's handled. */
    handle->flags |= UV_HANDLE_READ_PENDING;
    handle->reqs_pending++;
    return 0;
  }

  uv_tty_queue_read(loop, handle);

  return 0;
}