{
  uv_loop_t* loop = handle->loop;
  int err, nameSize;
  HANDLE pipeHandle = INVALID_HANDLE_VALUE;
  DWORD duplex_flags;

  UV_REQ_INIT(req, UV_CONNECT);
  req->handle = (uv_stream_t*) handle;
  req->cb = cb;

  /* Convert name to UTF16. */
  nameSize = MultiByteToWideChar(CP_UTF8, 0, name, -1, NULL, 0) * sizeof(WCHAR);
  handle->name = (WCHAR*)uv__malloc(nameSize);
  if (!handle->name) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  if (!MultiByteToWideChar(CP_UTF8,
                           0,
                           name,
                           -1,
                           handle->name,
                           nameSize / sizeof(WCHAR))) {
    err = GetLastError();
    goto error;
  }

  pipeHandle = open_named_pipe(handle->name, &duplex_flags);
  if (pipeHandle == INVALID_HANDLE_VALUE) {
    if (GetLastError() == ERROR_PIPE_BUSY) {
      /* Wait for the server to make a pipe instance available. */
      if (!QueueUserWorkItem(&pipe_connect_thread_proc,
                             req,
                             WT_EXECUTELONGFUNCTION)) {
        err = GetLastError();
        goto error;
      }

      REGISTER_HANDLE_REQ(loop, handle, req);
      handle->reqs_pending++;

      return;
    }

    err = GetLastError();
    goto error;
  }

  assert(pipeHandle != INVALID_HANDLE_VALUE);

  if (uv_set_pipe_handle(loop,
                         (uv_pipe_t*) req->handle,
                         pipeHandle,
                         -1,
                         duplex_flags)) {
    err = GetLastError();
    goto error;
  }

  SET_REQ_SUCCESS(req);
  uv_insert_pending_req(loop, (uv_req_t*) req);
  handle->reqs_pending++;
  REGISTER_HANDLE_REQ(loop, handle, req);
  return;

error:
  if (handle->name) {
    uv__free(handle->name);
    handle->name = NULL;
  }

  if (pipeHandle != INVALID_HANDLE_VALUE) {
    CloseHandle(pipeHandle);
  }

  /* Make this req pending reporting an error. */
  SET_REQ_ERROR(req, err);
  uv_insert_pending_req(loop, (uv_req_t*) req);
  handle->reqs_pending++;
  REGISTER_HANDLE_REQ(loop, handle, req);
  return;
}