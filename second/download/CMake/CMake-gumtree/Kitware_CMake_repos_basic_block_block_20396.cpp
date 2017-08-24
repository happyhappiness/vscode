{
    req = handle->stream.conn.shutdown_req;

    /* Clear the shutdown_req field so we don't go here again. */
    handle->stream.conn.shutdown_req = NULL;

    if (handle->flags & UV__HANDLE_CLOSING) {
      UNREGISTER_HANDLE_REQ(loop, handle, req);

      /* Already closing. Cancel the shutdown. */
      if (req->cb) {
        req->cb(req, UV_ECANCELED);
      }

      DECREASE_PENDING_REQ_COUNT(handle);
      return;
    }

    /* Try to avoid flushing the pipe buffer in the thread pool. */
    nt_status = pNtQueryInformationFile(handle->handle,
                                        &io_status,
                                        &pipe_info,
                                        sizeof pipe_info,
                                        FilePipeLocalInformation);

    if (nt_status != STATUS_SUCCESS) {
      /* Failure */
      UNREGISTER_HANDLE_REQ(loop, handle, req);

      handle->flags |= UV_HANDLE_WRITABLE; /* Questionable */
      if (req->cb) {
        err = pRtlNtStatusToDosError(nt_status);
        req->cb(req, uv_translate_sys_error(err));
      }

      DECREASE_PENDING_REQ_COUNT(handle);
      return;
    }

    if (pipe_info.OutboundQuota == pipe_info.WriteQuotaAvailable) {
      /* Short-circuit, no need to call FlushFileBuffers. */
      uv_insert_pending_req(loop, (uv_req_t*) req);
      return;
    }

    /* Run FlushFileBuffers in the thread pool. */
    result = QueueUserWorkItem(pipe_shutdown_thread_proc,
                               req,
                               WT_EXECUTELONGFUNCTION);
    if (result) {
      return;

    } else {
      /* Failure. */
      UNREGISTER_HANDLE_REQ(loop, handle, req);

      handle->flags |= UV_HANDLE_WRITABLE; /* Questionable */
      if (req->cb) {
        err = GetLastError();
        req->cb(req, uv_translate_sys_error(err));
      }

      DECREASE_PENDING_REQ_COUNT(handle);
      return;
    }
  }