(!GetNamedPipeHandleState(pipeHandle, &current_mode, NULL, NULL,
                                   NULL, NULL, 0)) {
        return -1;
      } else if (current_mode & PIPE_NOWAIT) {
        SetLastError(ERROR_ACCESS_DENIED);
        return -1;
      }