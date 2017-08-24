{
    /* Process the req without IOCP. */
    handle->flags |= UV_HANDLE_READ_PENDING;
    req->u.io.overlapped.InternalHigh = bytes;
    handle->reqs_pending++;
    uv_insert_pending_req(loop, (uv_req_t*)req);
  }