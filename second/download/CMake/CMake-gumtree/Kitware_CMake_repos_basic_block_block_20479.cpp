{
    /* Using overlapped IO, but wait for completion before returning */
    req->u.io.overlapped.hEvent = CreateEvent(NULL, 1, 0, NULL);
    if (!req->u.io.overlapped.hEvent) {
      uv_fatal_error(GetLastError(), "CreateEvent");
    }

    result = WriteFile(handle->handle,
                       bufs[0].base,
                       bufs[0].len,
                       NULL,
                       &req->u.io.overlapped);

    if (!result && GetLastError() != ERROR_IO_PENDING) {
      err = GetLastError();
      CloseHandle(req->u.io.overlapped.hEvent);
      return err;
    }

    if (result) {
      /* Request completed immediately. */
      req->u.io.queued_bytes = 0;
    } else {
      /* Request queued by the kernel. */
      req->u.io.queued_bytes = bufs[0].len;
      handle->write_queue_size += req->u.io.queued_bytes;
      if (WaitForSingleObject(req->u.io.overlapped.hEvent, INFINITE) !=
          WAIT_OBJECT_0) {
        err = GetLastError();
        CloseHandle(req->u.io.overlapped.hEvent);
        return uv_translate_sys_error(err);
      }
    }
    CloseHandle(req->u.io.overlapped.hEvent);

    REGISTER_HANDLE_REQ(loop, handle, req);
    handle->reqs_pending++;
    handle->stream.conn.write_reqs_pending++;
    return 0;
  }