{
  WSAPROTOCOL_INFOW protocol_info;
  int opt_len;
  int err;

  /* Detect the address family of the socket. */
  opt_len = (int) sizeof protocol_info;
  if (getsockopt(sock,
                 SOL_SOCKET,
                 SO_PROTOCOL_INFOW,
                 (char*) &protocol_info,
                 &opt_len) == SOCKET_ERROR) {
    return uv_translate_sys_error(GetLastError());
  }

  err = uv_udp_set_socket(handle->loop,
                          handle,
                          sock,
                          protocol_info.iAddressFamily);
  return uv_translate_sys_error(err);
}