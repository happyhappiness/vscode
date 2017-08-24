{
    /* The req will be processed with IOCP. */
    handle->flags |= UV_HANDLE_READ_PENDING;
    handle->reqs_pending++;
    if (handle->flags & UV_HANDLE_EMULATE_IOCP &&
        req->wait_handle == INVALID_HANDLE_VALUE &&
        !RegisterWaitForSingleObject(&req->wait_handle,
          req->event_handle, post_completion, (void*) req,
          INFINITE, WT_EXECUTEINWAITTHREAD)) {
      SET_REQ_ERROR(req, GetLastError());
      uv_insert_pending_req(loop, (uv_req_t*)req);
    }
  }