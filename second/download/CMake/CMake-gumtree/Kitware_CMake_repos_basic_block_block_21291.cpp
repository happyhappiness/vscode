{
    /* Request completed immediately. */
    req->u.io.queued_bytes = 0;
    handle->reqs_pending++;
    handle->send_queue_size += req->u.io.queued_bytes;
    handle->send_queue_count++;
    REGISTER_HANDLE_REQ(loop, handle, req);
    uv_insert_pending_req(loop, (uv_req_t*)req);
  }