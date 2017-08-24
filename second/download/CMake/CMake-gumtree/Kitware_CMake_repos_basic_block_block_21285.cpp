{
    handle->flags |= UV_HANDLE_ZERO_READ;

    buf.base = (char*) uv_zero_;
    buf.len = 0;
    flags = MSG_PEEK;

    result = handle->func_wsarecv(handle->socket,
                                  (WSABUF*) &buf,
                                  1,
                                  &bytes,
                                  &flags,
                                  &req->u.io.overlapped,
                                  NULL);

    if (UV_SUCCEEDED_WITHOUT_IOCP(result == 0)) {
      /* Process the req without IOCP. */
      handle->flags |= UV_HANDLE_READ_PENDING;
      req->u.io.overlapped.InternalHigh = bytes;
      handle->reqs_pending++;
      uv_insert_pending_req(loop, req);
    } else if (UV_SUCCEEDED_WITH_IOCP(result == 0)) {
      /* The req will be processed with IOCP. */
      handle->flags |= UV_HANDLE_READ_PENDING;
      handle->reqs_pending++;
    } else {
      /* Make this req pending reporting an error. */
      SET_REQ_ERROR(req, WSAGetLastError());
      uv_insert_pending_req(loop, req);
      handle->reqs_pending++;
    }
  }