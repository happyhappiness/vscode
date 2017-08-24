(i = 0; i < uv_simultaneous_server_accepts; i++) {
        uv_tcp_accept_t* req = &tcp->tcp.serv.accept_reqs[i];
        if (req->accept_socket != INVALID_SOCKET &&
            !HasOverlappedIoCompleted(&req->u.io.overlapped)) {
          closesocket(req->accept_socket);
          req->accept_socket = INVALID_SOCKET;
        }
      }