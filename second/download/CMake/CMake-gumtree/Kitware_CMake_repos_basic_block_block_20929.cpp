(REQ_SUCCESS(req) &&
      setsockopt(req->accept_socket,
                  SOL_SOCKET,
                  SO_UPDATE_ACCEPT_CONTEXT,
                  (char*)&handle->socket,
                  sizeof(handle->socket)) == 0) {
    req->next_pending = handle->tcp.serv.pending_accepts;
    handle->tcp.serv.pending_accepts = req;

    /* Accept and SO_UPDATE_ACCEPT_CONTEXT were successful. */
    if (handle->stream.serv.connection_cb) {
      handle->stream.serv.connection_cb((uv_stream_t*)handle, 0);
    }
  }