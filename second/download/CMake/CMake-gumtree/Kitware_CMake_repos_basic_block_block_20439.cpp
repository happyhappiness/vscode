{
  assert(handle->flags & UV_HANDLE_LISTENING);

  if (!firstInstance) {
    assert(req->pipeHandle == INVALID_HANDLE_VALUE);

    req->pipeHandle = CreateNamedPipeW(handle->name,
        PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES, 65536, 65536, 0, NULL);

    if (req->pipeHandle == INVALID_HANDLE_VALUE) {
      SET_REQ_ERROR(req, GetLastError());
      uv_insert_pending_req(loop, (uv_req_t*) req);
      handle->reqs_pending++;
      return;
    }

    if (uv_set_pipe_handle(loop, handle, req->pipeHandle, -1, 0)) {
      CloseHandle(req->pipeHandle);
      req->pipeHandle = INVALID_HANDLE_VALUE;
      SET_REQ_ERROR(req, GetLastError());
      uv_insert_pending_req(loop, (uv_req_t*) req);
      handle->reqs_pending++;
      return;
    }
  }

  assert(req->pipeHandle != INVALID_HANDLE_VALUE);

  /* Prepare the overlapped structure. */
  memset(&(req->u.io.overlapped), 0, sizeof(req->u.io.overlapped));

  if (!ConnectNamedPipe(req->pipeHandle, &req->u.io.overlapped) &&
      GetLastError() != ERROR_IO_PENDING) {
    if (GetLastError() == ERROR_PIPE_CONNECTED) {
      SET_REQ_SUCCESS(req);
    } else {
      CloseHandle(req->pipeHandle);
      req->pipeHandle = INVALID_HANDLE_VALUE;
      /* Make this req pending reporting an error. */
      SET_REQ_ERROR(req, GetLastError());
    }
    uv_insert_pending_req(loop, (uv_req_t*) req);
    handle->reqs_pending++;
    return;
  }

  handle->reqs_pending++;
}