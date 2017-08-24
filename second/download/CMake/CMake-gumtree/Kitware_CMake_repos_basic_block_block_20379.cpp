(current_mode & PIPE_NOWAIT) {
        SetLastError(ERROR_ACCESS_DENIED);
        return -1;
      }