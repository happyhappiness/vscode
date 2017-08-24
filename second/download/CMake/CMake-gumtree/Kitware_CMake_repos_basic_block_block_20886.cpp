(UV_SUCCEEDED_WITHOUT_IOCP(success)) {
    /* Process the req without IOCP. */
    handle->reqs_pending++;
    REGISTER_HANDLE_REQ(loop, handle, req);
    uv_insert_pending_req(loop, (uv_req_t*)req);
  } else if (UV_SUCCEEDED_WITH_IOCP(success)) {
    /* The req will be processed with IOCP. */
    handle->reqs_pending++;
    REGISTER_HANDLE_REQ(loop, handle, req);
  } else {
    return WSAGetLastError();
  }