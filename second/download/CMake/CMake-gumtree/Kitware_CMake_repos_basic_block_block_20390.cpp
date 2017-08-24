{
    assert(!(handle->flags & UV_HANDLE_CLOSED));

    if (handle->flags & UV_HANDLE_CONNECTION) {
      /* Free pending sockets */
      while (!QUEUE_EMPTY(&handle->pipe.conn.pending_ipc_info.queue)) {
        QUEUE* q;
        SOCKET socket;

        q = QUEUE_HEAD(&handle->pipe.conn.pending_ipc_info.queue);
        QUEUE_REMOVE(q);
        item = QUEUE_DATA(q, uv__ipc_queue_item_t, member);

        /* Materialize socket and close it */
        socket = WSASocketW(FROM_PROTOCOL_INFO,
                            FROM_PROTOCOL_INFO,
                            FROM_PROTOCOL_INFO,
                            &item->socket_info_ex.socket_info,
                            0,
                            WSA_FLAG_OVERLAPPED);
        uv__free(item);

        if (socket != INVALID_SOCKET)
          closesocket(socket);
      }
      handle->pipe.conn.pending_ipc_info.queue_len = 0;

      if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
        if (handle->read_req.wait_handle != INVALID_HANDLE_VALUE) {
          UnregisterWait(handle->read_req.wait_handle);
          handle->read_req.wait_handle = INVALID_HANDLE_VALUE;
        }
        if (handle->read_req.event_handle) {
          CloseHandle(handle->read_req.event_handle);
          handle->read_req.event_handle = NULL;
        }
      }
    }

    if (handle->flags & UV_HANDLE_PIPESERVER) {
      assert(handle->pipe.serv.accept_reqs);
      uv__free(handle->pipe.serv.accept_reqs);
      handle->pipe.serv.accept_reqs = NULL;
    }

    uv__handle_close(handle);
  }