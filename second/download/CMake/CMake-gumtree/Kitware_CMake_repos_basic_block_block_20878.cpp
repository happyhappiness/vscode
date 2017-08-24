{
  uv_loop_t* loop = server->loop;
  int err = 0;
  int family;

  uv_tcp_accept_t* req = server->tcp.serv.pending_accepts;

  if (!req) {
    /* No valid connections found, so we error out. */
    return WSAEWOULDBLOCK;
  }

  if (req->accept_socket == INVALID_SOCKET) {
    return WSAENOTCONN;
  }

  if (server->flags & UV_HANDLE_IPV6) {
    family = AF_INET6;
  } else {
    family = AF_INET;
  }

  err = uv_tcp_set_socket(client->loop,
                          client,
                          req->accept_socket,
                          family,
                          0);
  if (err) {
    closesocket(req->accept_socket);
  } else {
    uv_connection_init((uv_stream_t*) client);
    /* AcceptEx() implicitly binds the accepted socket. */
    client->flags |= UV_HANDLE_BOUND | UV_HANDLE_READABLE | UV_HANDLE_WRITABLE;
  }

  /* Prepare the req to pick up a new connection */
  server->tcp.serv.pending_accepts = req->next_pending;
  req->next_pending = NULL;
  req->accept_socket = INVALID_SOCKET;

  if (!(server->flags & UV__HANDLE_CLOSING)) {
    /* Check if we're in a middle of changing the number of pending accepts. */
    if (!(server->flags & UV_HANDLE_TCP_ACCEPT_STATE_CHANGING)) {
      uv_tcp_queue_accept(server, req);
    } else {
      /* We better be switching to a single pending accept. */
      assert(server->flags & UV_HANDLE_TCP_SINGLE_ACCEPT);

      server->tcp.serv.processed_accepts++;

      if (server->tcp.serv.processed_accepts >= uv_simultaneous_server_accepts) {
        server->tcp.serv.processed_accepts = 0;
        /*
         * All previously queued accept requests are now processed.
         * We now switch to queueing just a single accept.
         */
        uv_tcp_queue_accept(server, &server->tcp.serv.accept_reqs[0]);
        server->flags &= ~UV_HANDLE_TCP_ACCEPT_STATE_CHANGING;
        server->flags |= UV_HANDLE_TCP_SINGLE_ACCEPT;
      }
    }
  }

  loop->active_tcp_streams++;

  return err;
}