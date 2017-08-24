(listen(handle->socket, SOMAXCONN) == SOCKET_ERROR) {
          handle->delayed_error = WSAGetLastError();
        }