{
    assert(!(handle->flags & UV_HANDLE_NON_OVERLAPPED_PIPE));
    ipc_frame.header.flags = 0;

    /* Use the IPC framing protocol. */
    if (send_handle) {
      tcp_send_handle = (uv_tcp_t*)send_handle;

      if (handle->pipe.conn.ipc_pid == 0) {
          handle->pipe.conn.ipc_pid = uv_current_pid();
      }

      err = uv_tcp_duplicate_socket(tcp_send_handle, handle->pipe.conn.ipc_pid,
          &ipc_frame.socket_info_ex.socket_info);
      if (err) {
        return err;
      }

      ipc_frame.socket_info_ex.delayed_error = tcp_send_handle->delayed_error;

      ipc_frame.header.flags |= UV_IPC_TCP_SERVER;

      if (tcp_send_handle->flags & UV_HANDLE_CONNECTION) {
        ipc_frame.header.flags |= UV_IPC_TCP_CONNECTION;
      }
    }

    if (nbufs == 1) {
      ipc_frame.header.flags |= UV_IPC_RAW_DATA;
      ipc_frame.header.raw_data_length = bufs[0].len;
    }

    /*
     * Use the provided req if we're only doing a single write.
     * If we're doing multiple writes, use ipc_header_write_req to do
     * the first write, and then use the provided req for the second write.
     */
    if (!(ipc_frame.header.flags & UV_IPC_RAW_DATA)) {
      ipc_header_req = req;
    } else {
      /*
       * Try to use the preallocated write req if it's available.
       * Otherwise allocate a new one.
       */
      if (handle->pipe.conn.ipc_header_write_req.type != UV_WRITE) {
        ipc_header_req = (uv_write_t*)&handle->pipe.conn.ipc_header_write_req;
      } else {
        ipc_header_req = (uv_write_t*)uv__malloc(sizeof(uv_write_t));
        if (!ipc_header_req) {
          uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
        }
      }

      UV_REQ_INIT(ipc_header_req, UV_WRITE);
      ipc_header_req->handle = (uv_stream_t*) handle;
      ipc_header_req->cb = NULL;
      ipc_header_req->ipc_header = 1;
    }

    /* Write the header or the whole frame. */
    memset(&ipc_header_req->u.io.overlapped, 0,
           sizeof(ipc_header_req->u.io.overlapped));

    /* Using overlapped IO, but wait for completion before returning.
       This write is blocking because ipc_frame is on stack. */
    ipc_header_req->u.io.overlapped.hEvent = CreateEvent(NULL, 1, 0, NULL);
    if (!ipc_header_req->u.io.overlapped.hEvent) {
      uv_fatal_error(GetLastError(), "CreateEvent");
    }

    result = WriteFile(handle->handle,
                        &ipc_frame,
                        ipc_frame.header.flags & UV_IPC_TCP_SERVER ?
                          sizeof(ipc_frame) : sizeof(ipc_frame.header),
                        NULL,
                        &ipc_header_req->u.io.overlapped);
    if (!result && GetLastError() != ERROR_IO_PENDING) {
      err = GetLastError();
      CloseHandle(ipc_header_req->u.io.overlapped.hEvent);
      return err;
    }

    if (!result) {
      /* Request not completed immediately. Wait for it.*/
      if (WaitForSingleObject(ipc_header_req->u.io.overlapped.hEvent, INFINITE) !=
          WAIT_OBJECT_0) {
        err = GetLastError();
        CloseHandle(ipc_header_req->u.io.overlapped.hEvent);
        return err;
      }
    }
    ipc_header_req->u.io.queued_bytes = 0;
    CloseHandle(ipc_header_req->u.io.overlapped.hEvent);
    ipc_header_req->u.io.overlapped.hEvent = NULL;

    REGISTER_HANDLE_REQ(loop, handle, ipc_header_req);
    handle->reqs_pending++;
    handle->stream.conn.write_reqs_pending++;

    /* If we don't have any raw data to write - we're done. */
    if (!(ipc_frame.header.flags & UV_IPC_RAW_DATA)) {
      return 0;
    }
  }