(req->pipeHandle != INVALID_HANDLE_VALUE) {
      CloseHandle(req->pipeHandle);
      req->pipeHandle = INVALID_HANDLE_VALUE;
    }