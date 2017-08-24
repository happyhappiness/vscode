{
  unsigned int i, simultaneous_accepts;
  uv_tcp_accept_t* req;
  int err;

  assert(backlog > 0);

  if (handle->flags & UV_HANDLE_LISTENING) {
    handle->stream.serv.connection_cb = cb;
  }

  if (handle->flags & UV_HANDLE_READING) {
    return WSAEISCONN;
  }

  if (handle->delayed_error) {
    return handle->delayed_error;
  }

  if (!(handle->flags & UV_HANDLE_BOUND)) {
    err = uv_tcp_try_bind(handle,
                          (const struct sockaddr*) &uv_addr_ip4_any_,
                          sizeof(uv_addr_ip4_any_),
                          0);
    if (err)
      return err;
    if (handle->delayed_error)
      return handle->delayed_error;
  }

  if (!handle->tcp.serv.func_acceptex) {
    if (!uv_get_acceptex_function(handle->socket, &handle->tcp.serv.func_acceptex)) {
      return WSAEAFNOSUPPORT;
    }
  }

  if (!(handle->flags & UV_HANDLE_SHARED_TCP_SOCKET) &&
      listen(handle->socket, backlog) == SOCKET_ERROR) {
    return WSAGetLastError();
  }

  handle->flags |= UV_HANDLE_LISTENING;
  handle->stream.serv.connection_cb = cb;
  INCREASE_ACTIVE_COUNT(loop, handle);

  simultaneous_accepts = handle->flags & UV_HANDLE_TCP_SINGLE_ACCEPT ? 1
    : uv_simultaneous_server_accepts;

  if(!handle->tcp.serv.accept_reqs) {
    handle->tcp.serv.accept_reqs = (uv_tcp_accept_t*)
      uv__malloc(uv_simultaneous_server_accepts * sizeof(uv_tcp_accept_t));
    if (!handle->tcp.serv.accept_reqs) {
      uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
    }

    for (i = 0; i < simultaneous_accepts; i++) {
      req = &handle->tcp.serv.accept_reqs[i];
      UV_REQ_INIT(req, UV_ACCEPT);
      req->accept_socket = INVALID_SOCKET;
      req->data = handle;

      req->wait_handle = INVALID_HANDLE_VALUE;
      if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
        req->event_handle = CreateEvent(NULL, 0, 0, NULL);
        if (!req->event_handle) {
          uv_fatal_error(GetLastError(), "CreateEvent");
        }
      } else {
        req->event_handle = NULL;
      }

      uv_tcp_queue_accept(handle, req);
    }

    /* Initialize other unused requests too, because uv_tcp_endgame */
    /* doesn't know how how many requests were initialized, so it will */
    /* try to clean up {uv_simultaneous_server_accepts} requests. */
    for (i = simultaneous_accepts; i < uv_simultaneous_server_accepts; i++) {
      req = &handle->tcp.serv.accept_reqs[i];
      UV_REQ_INIT(req, UV_ACCEPT);
      req->accept_socket = INVALID_SOCKET;
      req->data = handle;
      req->wait_handle = INVALID_HANDLE_VALUE;
      req->event_handle = NULL;
    }
  }

  return 0;
}