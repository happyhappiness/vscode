{
      req = &handle->tcp.serv.accept_reqs[i];
      UV_REQ_INIT(req, UV_ACCEPT);
      req->accept_socket = INVALID_SOCKET;
      req->data = handle;
      req->wait_handle = INVALID_HANDLE_VALUE;
      req->event_handle = NULL;
    }