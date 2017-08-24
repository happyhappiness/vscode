{
  WSAPROTOCOL_INFOW protocol_info;
  int len;
  SOCKET peer_socket, base_socket;
  DWORD bytes;
  DWORD yes = 1;

  /* Set the socket to nonblocking mode */
  if (ioctlsocket(socket, FIONBIO, &yes) == SOCKET_ERROR)
    return uv_translate_sys_error(WSAGetLastError());

  /* Try to obtain a base handle for the socket. This increases this chances */
  /* that we find an AFD handle and are able to use the fast poll mechanism. */
  /* This will always fail on windows XP/2k3, since they don't support the */
  /* SIO_BASE_HANDLE ioctl. */
#ifndef NDEBUG
  base_socket = INVALID_SOCKET;
#endif

  if (WSAIoctl(socket,
               SIO_BASE_HANDLE,
               NULL,
               0,
               &base_socket,
               sizeof base_socket,
               &bytes,
               NULL,
               NULL) == 0) {
    assert(base_socket != 0 && base_socket != INVALID_SOCKET);
    socket = base_socket;
  }

  uv__handle_init(loop, (uv_handle_t*) handle, UV_POLL);
  handle->socket = socket;
  handle->events = 0;

  /* Obtain protocol information about the socket. */
  len = sizeof protocol_info;
  if (getsockopt(socket,
                 SOL_SOCKET,
                 SO_PROTOCOL_INFOW,
                 (char*) &protocol_info,
                 &len) != 0) {
    return uv_translate_sys_error(WSAGetLastError());
  }

  /* Get the peer socket that is needed to enable fast poll. If the returned */
  /* value is NULL, the protocol is not implemented by MSAFD and we'll have */
  /* to use slow mode. */
  peer_socket = uv__fast_poll_get_peer_socket(loop, &protocol_info);

  if (peer_socket != INVALID_SOCKET) {
    /* Initialize fast poll specific fields. */
    handle->peer_socket = peer_socket;
  } else {
    /* Initialize slow poll specific fields. */
    handle->flags |= UV_HANDLE_POLL_SLOW;
  }

  /* Initialize 2 poll reqs. */
  handle->submitted_events_1 = 0;
  UV_REQ_INIT(&handle->poll_req_1, UV_POLL_REQ);
  handle->poll_req_1.data = handle;

  handle->submitted_events_2 = 0;
  UV_REQ_INIT(&handle->poll_req_2, UV_POLL_REQ);
  handle->poll_req_2.data = handle;

  return 0;
}