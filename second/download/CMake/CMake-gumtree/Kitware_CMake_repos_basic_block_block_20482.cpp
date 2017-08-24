{
    result = WriteFile(handle->handle,
                       bufs[0].base,
                       bufs[0].len,
                       NULL,
                       &req->u.io.overlapped);

    if (!result && GetLastError() != ERROR_IO_PENDING) {
      return GetLastError();
    }

    if (result) {
      /* Request completed immediately. */
      req->u.io.queued_bytes = 0;
    } else {
      /* Request queued by the kernel. */
      req->u.io.queued_bytes = bufs[0].len;
      handle->write_queue_size += req->u.io.queued_bytes;
    }

    if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
      req->event_handle = CreateEvent(NULL, 0, 0, NULL);
      if (!req->event_handle) {
        uv_fatal_error(GetLastError(), "CreateEvent");
      }
      if (!RegisterWaitForSingleObject(&req->wait_handle,
          req->u.io.overlapped.hEvent, post_completion_write_wait, (void*) req,
          INFINITE, WT_EXECUTEINWAITTHREAD)) {
        return GetLastError();
      }
    }
  }