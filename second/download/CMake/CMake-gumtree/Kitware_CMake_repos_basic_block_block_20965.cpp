((tcp->flags & UV_HANDLE_SHARED_TCP_SOCKET) &&
             tcp->tcp.serv.accept_reqs != NULL) {
    /* Under normal circumstances closesocket() will ensure that all pending */
    /* accept reqs are canceled. However, when the socket is shared the */
    /* presence of another reference to the socket in another process will */
    /* keep the accept reqs going, so we have to ensure that these are */
    /* canceled. */
    if (uv_tcp_try_cancel_io(tcp) != 0) {
      /* When cancellation is not possible, there is another option: we can */
      /* close the incoming sockets, which will also cancel the accept */
      /* operations. However this is not cool because we might inadvertently */
      /* close a socket that just accepted a new connection, which will */
      /* cause the connection to be aborted. */
      unsigned int i;
      for (i = 0; i < uv_simultaneous_server_accepts; i++) {
        uv_tcp_accept_t* req = &tcp->tcp.serv.accept_reqs[i];
        if (req->accept_socket != INVALID_SOCKET &&
            !HasOverlappedIoCompleted(&req->u.io.overlapped)) {
          closesocket(req->accept_socket);
          req->accept_socket = INVALID_SOCKET;
        }
      }
    }
  }