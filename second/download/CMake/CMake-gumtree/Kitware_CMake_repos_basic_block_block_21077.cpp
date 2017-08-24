{
  uv_read_t* req;
  BOOL r;

  assert(handle->flags & UV_HANDLE_READING);
  assert(!(handle->flags & UV_HANDLE_READ_PENDING));
  assert(handle->handle && handle->handle != INVALID_HANDLE_VALUE);

  req = &handle->read_req;
  memset(&req->u.io.overlapped, 0, sizeof(req->u.io.overlapped));

  handle->tty.rd.read_line_buffer = uv_buf_init(NULL, 0);
  handle->alloc_cb((uv_handle_t*) handle, 8192, &handle->tty.rd.read_line_buffer);
  if (handle->tty.rd.read_line_buffer.base == NULL ||
      handle->tty.rd.read_line_buffer.len == 0) {
    handle->read_cb((uv_stream_t*) handle,
                    UV_ENOBUFS,
                    &handle->tty.rd.read_line_buffer);
    return;
  }
  assert(handle->tty.rd.read_line_buffer.base != NULL);

  /* Reset flags  No locking is required since there cannot be a line read
     in progress. We are also relying on the memory barrier provided by
     QueueUserWorkItem*/
  uv__restore_screen_state = FALSE;
  uv__read_console_status = NOT_STARTED;
  r = QueueUserWorkItem(uv_tty_line_read_thread,
                        (void*) req,
                        WT_EXECUTELONGFUNCTION);
  if (!r) {
    SET_REQ_ERROR(req, GetLastError());
    uv_insert_pending_req(loop, (uv_req_t*)req);
  }

  handle->flags |= UV_HANDLE_READ_PENDING;
  handle->reqs_pending++;
}