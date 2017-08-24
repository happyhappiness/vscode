(shutdown(handle->socket, SD_SEND) == SOCKET_ERROR) {
      err = WSAGetLastError();
    }