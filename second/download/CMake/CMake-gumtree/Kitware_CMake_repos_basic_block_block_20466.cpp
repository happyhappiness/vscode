{
    memset(&req->u.io.overlapped, 0, sizeof(req->u.io.overlapped));
    if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
      req->u.io.overlapped.hEvent = (HANDLE) ((uintptr_t) req->event_handle | 1);
    }

    /* Do 0-read */
    result = ReadFile(handle->handle,
                      &uv_zero_,
                      0,
                      NULL,
                      &req->u.io.overlapped);

    if (!result && GetLastError() != ERROR_IO_PENDING) {
      /* Make this req pending reporting an error. */
      SET_REQ_ERROR(req, GetLastError());
      goto error;
    }

    if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
      if (!req->event_handle) {
        req->event_handle = CreateEvent(NULL, 0, 0, NULL);
        if (!req->event_handle) {
          uv_fatal_error(GetLastError(), "CreateEvent");
        }
      }
      if (req->wait_handle == INVALID_HANDLE_VALUE) {
        if (!RegisterWaitForSingleObject(&req->wait_handle,
            req->u.io.overlapped.hEvent, post_completion_read_wait, (void*) req,
            INFINITE, WT_EXECUTEINWAITTHREAD)) {
          SET_REQ_ERROR(req, GetLastError());
          goto error;
        }
      }
    }
  }