{
    handle->tty.rd.read_raw_wait = NULL;
    SET_REQ_ERROR(req, GetLastError());
    uv_insert_pending_req(loop, (uv_req_t*)req);
  }