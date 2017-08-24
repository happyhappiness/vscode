{
  uv_pipe_accept_t* req = (uv_pipe_accept_t*) raw_req;

  assert(handle->type == UV_NAMED_PIPE);

  if (handle->flags & UV__HANDLE_CLOSING) {
    /* The req->pipeHandle should be freed already in uv_pipe_cleanup(). */
    assert(req->pipeHandle == INVALID_HANDLE_VALUE);
    DECREASE_PENDING_REQ_COUNT(handle);
    return;
  }

  if (REQ_SUCCESS(req)) {
    assert(req->pipeHandle != INVALID_HANDLE_VALUE);
    req->next_pending = handle->pipe.serv.pending_accepts;
    handle->pipe.serv.pending_accepts = req;

    if (handle->stream.serv.connection_cb) {
      handle->stream.serv.connection_cb((uv_stream_t*)handle, 0);
    }
  } else {
    if (req->pipeHandle != INVALID_HANDLE_VALUE) {
      CloseHandle(req->pipeHandle);
      req->pipeHandle = INVALID_HANDLE_VALUE;
    }
    if (!(handle->flags & UV__HANDLE_CLOSING)) {
      uv_pipe_queue_accept(loop, handle, req, FALSE);
    }
  }

  DECREASE_PENDING_REQ_COUNT(handle);
}