{
  uv_loop_t* loop = server->loop;
  uv_pipe_t* pipe_client;
  uv_pipe_accept_t* req;
  QUEUE* q;
  uv__ipc_queue_item_t* item;
  int err;

  if (server->ipc) {
    if (QUEUE_EMPTY(&server->pipe.conn.pending_ipc_info.queue)) {
      /* No valid pending sockets. */
      return WSAEWOULDBLOCK;
    }

    q = QUEUE_HEAD(&server->pipe.conn.pending_ipc_info.queue);
    QUEUE_REMOVE(q);
    server->pipe.conn.pending_ipc_info.queue_len--;
    item = QUEUE_DATA(q, uv__ipc_queue_item_t, member);

    err = uv_tcp_import((uv_tcp_t*)client,
                        &item->socket_info_ex,
                        item->tcp_connection);
    if (err != 0)
      return err;

    uv__free(item);

  } else {
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

  return 0;
}