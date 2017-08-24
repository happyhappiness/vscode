{
    CloseHandle(handle->pipe.serv.accept_reqs[0].pipeHandle);
    handle->pipe.serv.accept_reqs[0].pipeHandle = INVALID_HANDLE_VALUE;
  }