{
    /* Error related to accepted socket is ignored because the server */
    /* socket may still be healthy. If the server socket is broken */
    /* uv_queue_accept will detect it. */
    closesocket(req->accept_socket);
    req->accept_socket = INVALID_SOCKET;
    if (handle->flags & UV_HANDLE_LISTENING) {
      uv_tcp_queue_accept(handle, req);
    }
  }