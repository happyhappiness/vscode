(!(server->flags & UV_HANDLE_TCP_ACCEPT_STATE_CHANGING)) {
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