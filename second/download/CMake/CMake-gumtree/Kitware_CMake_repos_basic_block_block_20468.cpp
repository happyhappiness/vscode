{
    req->next_req =
      handle->pipe.conn.non_overlapped_writes_tail->next_req;
    handle->pipe.conn.non_overlapped_writes_tail->next_req = (uv_req_t*)req;
    handle->pipe.conn.non_overlapped_writes_tail = req;
  }