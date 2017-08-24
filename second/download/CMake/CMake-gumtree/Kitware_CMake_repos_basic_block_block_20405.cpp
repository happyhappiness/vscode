{
  uv_loop_t* loop = handle->loop;
  int i, err, nameSize;
  uv_pipe_accept_t* req;

  if (handle->flags & UV_HANDLE_BOUND) {
    return UV_EINVAL;
  }

  if (!name) {
    return UV_EINVAL;
  }

  if (!(handle->flags & UV_HANDLE_PIPESERVER)) {
    handle->pipe.serv.pending_instances = default_pending_pipe_instances;
  }

  handle->pipe.serv.accept_reqs = (uv_pipe_accept_t*)
    uv__malloc(sizeof(uv_pipe_accept_t) * handle->pipe.serv.pending_instances);
  if (!handle->pipe.serv.accept_reqs) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  for (i = 0; i < handle->pipe.serv.pending_instances; i++) {
    req = &handle->pipe.serv.accept_reqs[i];
    UV_REQ_INIT(req, UV_ACCEPT);
    req->data = handle;
    req->pipeHandle = INVALID_HANDLE_VALUE;
    req->next_pending = NULL;
  }

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

  /*
   * Attempt to create the first pipe with FILE_FLAG_FIRST_PIPE_INSTANCE.
   * If this fails then there's already a pipe server for the given pipe name.
   */
  handle->pipe.serv.accept_reqs[0].pipeHandle = CreateNamedPipeW(handle->name,
      PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED |
      FILE_FLAG_FIRST_PIPE_INSTANCE,
      PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
      PIPE_UNLIMITED_INSTANCES, 65536, 65536, 0, NULL);

  if (handle->pipe.serv.accept_reqs[0].pipeHandle == INVALID_HANDLE_VALUE) {
    err = GetLastError();
    if (err == ERROR_ACCESS_DENIED) {
      err = WSAEADDRINUSE;  /* Translates to UV_EADDRINUSE. */
    } else if (err == ERROR_PATH_NOT_FOUND || err == ERROR_INVALID_NAME) {
      err = WSAEACCES;  /* Translates to UV_EACCES. */
    }
    goto error;
  }

  if (uv_set_pipe_handle(loop,
                         handle,
                         handle->pipe.serv.accept_reqs[0].pipeHandle,
                         -1,
                         0)) {
    err = GetLastError();
    goto error;
  }

  handle->pipe.serv.pending_accepts = NULL;
  handle->flags |= UV_HANDLE_PIPESERVER;
  handle->flags |= UV_HANDLE_BOUND;

  return 0;

error:
  if (handle->name) {
    uv__free(handle->name);
    handle->name = NULL;
  }

  if (handle->pipe.serv.accept_reqs[0].pipeHandle != INVALID_HANDLE_VALUE) {
    CloseHandle(handle->pipe.serv.accept_reqs[0].pipeHandle);
    handle->pipe.serv.accept_reqs[0].pipeHandle = INVALID_HANDLE_VALUE;
  }

  return uv_translate_sys_error(err);
}