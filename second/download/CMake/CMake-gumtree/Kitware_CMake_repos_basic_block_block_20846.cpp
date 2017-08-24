{
    /* Make this req pending reporting an error. */
    SET_REQ_ERROR(req, WSAGetLastError());
    uv_insert_pending_req(loop, (uv_req_t*)req);
    handle->reqs_pending++;
    /* Destroy the preallocated client socket. */
    closesocket(accept_socket);
    /* Destroy the event handle */
    if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
      CloseHandle(req->u.io.overlapped.hEvent);
      req->event_handle = NULL;
    }
  }