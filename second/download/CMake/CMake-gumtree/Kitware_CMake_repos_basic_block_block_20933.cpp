{
  int err;
  SOCKET socket = WSASocketW(FROM_PROTOCOL_INFO,
                             FROM_PROTOCOL_INFO,
                             FROM_PROTOCOL_INFO,
                             &socket_info_ex->socket_info,
                             0,
                             WSA_FLAG_OVERLAPPED);

  if (socket == INVALID_SOCKET) {
    return WSAGetLastError();
  }

  err = uv_tcp_set_socket(tcp->loop,
                          tcp,
                          socket,
                          socket_info_ex->socket_info.iAddressFamily,
                          1);
  if (err) {
    closesocket(socket);
    return err;
  }

  if (tcp_connection) {
    uv_connection_init((uv_stream_t*)tcp);
    tcp->flags |= UV_HANDLE_READABLE | UV_HANDLE_WRITABLE;
  }

  tcp->flags |= UV_HANDLE_BOUND;
  tcp->flags |= UV_HANDLE_SHARED_TCP_SOCKET;

  tcp->delayed_error = socket_info_ex->delayed_error;

  tcp->loop->active_tcp_streams++;
  return 0;
}