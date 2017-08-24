{
  uv_loop_t* loop = handle->loop;
  int i;

  if (handle->flags & UV_HANDLE_LISTENING) {
    handle->stream.serv.connection_cb = cb;
  }

  if (!(handle->flags & UV_HANDLE_BOUND)) {
    return WSAEINVAL;
  }

  if (handle->flags & UV_HANDLE_READING) {
    return WSAEISCONN;
  }

  if (!(handle->flags & UV_HANDLE_PIPESERVER)) {
    return ERROR_NOT_SUPPORTED;
  }

  handle->flags |= UV_HANDLE_LISTENING;
  INCREASE_ACTIVE_COUNT(loop, handle);
  handle->stream.serv.connection_cb = cb;

  /* First pipe handle should have already been created in uv_pipe_bind */
  assert(handle->pipe.serv.accept_reqs[0].pipeHandle != INVALID_HANDLE_VALUE);

  for (i = 0; i < handle->pipe.serv.pending_instances; i++) {
    uv_pipe_queue_accept(loop, handle, &handle->pipe.serv.accept_reqs[i], i == 0);
  }

  return 0;
}