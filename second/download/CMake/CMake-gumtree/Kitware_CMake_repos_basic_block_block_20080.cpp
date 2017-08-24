{
    /* Make this req pending reporting an error. */
    SET_REQ_ERROR(&handle->req, GetLastError());
    uv_insert_pending_req(loop, (uv_req_t*)&handle->req);
  }