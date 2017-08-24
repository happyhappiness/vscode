(pipeHandle != INVALID_HANDLE_VALUE) {
      *duplex_flags = UV_HANDLE_WRITABLE;
      return pipeHandle;
    }