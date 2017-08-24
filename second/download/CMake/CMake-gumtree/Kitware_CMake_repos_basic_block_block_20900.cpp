{
    /* Request queued by the kernel. */
    req->u.io.queued_bytes = uv__count_bufs(bufs, nbufs);
    handle->reqs_pending++;
    handle->stream.conn.write_reqs_pending++;
    REGISTER_HANDLE_REQ(loop, handle, req);
    handle->write_queue_size += req->u.io.queued_bytes;
    if (handle->flags & UV_HANDLE_EMULATE_IOCP &&
        !RegisterWaitForSingleObject(&req->wait_handle,
          req->event_handle, post_write_completion, (void*) req,
          INFINITE, WT_EXECUTEINWAITTHREAD | WT_EXECUTEONLYONCE)) {
      SET_REQ_ERROR(req, GetLastError());
      uv_insert_pending_req(loop, (uv_req_t*)req);
    }
  }