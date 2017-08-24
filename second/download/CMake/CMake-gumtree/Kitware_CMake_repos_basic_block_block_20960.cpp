(req->accept_socket != INVALID_SOCKET &&
            !HasOverlappedIoCompleted(&req->u.io.overlapped)) {
          closesocket(req->accept_socket);
          req->accept_socket = INVALID_SOCKET;
        }