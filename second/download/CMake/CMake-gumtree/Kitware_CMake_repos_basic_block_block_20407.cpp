{
    req = &handle->pipe.serv.accept_reqs[i];
    UV_REQ_INIT(req, UV_ACCEPT);
    req->data = handle;
    req->pipeHandle = INVALID_HANDLE_VALUE;
    req->next_pending = NULL;
  }