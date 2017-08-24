{
          closesocket(req->accept_socket);
          req->accept_socket = INVALID_SOCKET;
        }