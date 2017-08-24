{
    /* Process the req without IOCP. */
    req->accept_socket = accept_socket;
    handle->reqs_pending++;
    uv_insert_pending_req(loop, (uv_req_t*)req);
  }