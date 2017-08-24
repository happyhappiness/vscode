{
    for (i = 0; i < handle->pipe.serv.pending_instances; i++) {
      pipeHandle = handle->pipe.serv.accept_reqs[i].pipeHandle;
      if (pipeHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(pipeHandle);
        handle->pipe.serv.accept_reqs[i].pipeHandle = INVALID_HANDLE_VALUE;
      }
    }
    handle->handle = INVALID_HANDLE_VALUE;
  }