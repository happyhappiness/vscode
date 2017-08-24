(pipeHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(pipeHandle);
        handle->pipe.serv.accept_reqs[i].pipeHandle = INVALID_HANDLE_VALUE;
      }