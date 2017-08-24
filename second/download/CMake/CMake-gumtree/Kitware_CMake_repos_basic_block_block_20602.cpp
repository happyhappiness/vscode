{
    /* Make this req pending, reporting an error. */
    SET_REQ_ERROR(req, GetLastError());
    uv_insert_pending_req(loop, req);
  }