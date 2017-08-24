{
    SOCKET sock;
    DWORD err;

    sock = socket(domain, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
      err = WSAGetLastError();
      QUEUE_REMOVE(&handle->handle_queue);
      return uv_translate_sys_error(err);
    }

    err = uv_tcp_set_socket(handle->loop, handle, sock, domain, 0);
    if (err) {
      closesocket(sock);
      QUEUE_REMOVE(&handle->handle_queue);
      return uv_translate_sys_error(err);
    }

  }