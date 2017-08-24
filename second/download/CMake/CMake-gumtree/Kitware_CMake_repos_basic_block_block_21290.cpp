{
    /* Request queued by the kernel. */
    req->u.io.queued_bytes = uv__count_bufs(bufs, nbufs);
    handle->reqs_pending++;
    handle->send_queue_size += req->u.io.queued_bytes;
    handle->send_queue_count++;
    REGISTER_HANDLE_REQ(loop, handle, req);
  }