{
    SET_REQ_ERROR(req, WSAGetLastError());
    uv_insert_pending_req(loop, (uv_req_t*)req);
    handle->reqs_pending++;
    return;
  }