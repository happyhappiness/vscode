{
    /* Request completed immediately. */
    req->u.io.queued_bytes = 0;
    handle->reqs_pending++;
    handle->stream.conn.write_reqs_pending++;
    REGISTER_HANDLE_REQ(loop, handle, req);
    uv_insert_pending_req(loop, (uv_req_t*) req);
  }