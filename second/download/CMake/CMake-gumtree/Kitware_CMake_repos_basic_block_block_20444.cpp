{
    pipe_client = (uv_pipe_t*)client;

    /* Find a connection instance that has been connected, but not yet */
    /* accepted. */
    req = server->pipe.serv.pending_accepts;

    if (!req) {
      /* No valid connections found, so we error out. */
      return WSAEWOULDBLOCK;
    }

    /* Initialize the client handle and copy the pipeHandle to the client */
    uv_pipe_connection_init(pipe_client);
    pipe_client->handle = req->pipeHandle;
    pipe_client->flags |= UV_HANDLE_READABLE | UV_HANDLE_WRITABLE;

    /* Prepare the req to pick up a new connection */
    server->pipe.serv.pending_accepts = req->next_pending;
    req->next_pending = NULL;
    req->pipeHandle = INVALID_HANDLE_VALUE;

    if (!(server->flags & UV__HANDLE_CLOSING)) {
      uv_pipe_queue_accept(loop, server, req, FALSE);
    }
  }