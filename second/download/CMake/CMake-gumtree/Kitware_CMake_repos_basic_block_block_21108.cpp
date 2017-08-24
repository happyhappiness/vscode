{
    SET_REQ_SUCCESS(&handle->read_req);
    uv_insert_pending_req(handle->loop, (uv_req_t*) &handle->read_req);
    /* Make sure no attempt is made to insert it again until it's handled. */
    handle->flags |= UV_HANDLE_READ_PENDING;
    handle->reqs_pending++;
    return 0;
  }