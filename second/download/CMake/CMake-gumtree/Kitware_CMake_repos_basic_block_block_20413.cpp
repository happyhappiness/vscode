(WaitNamedPipeW(handle->name, 30000)) {
    /* The pipe is now available, try to connect. */
    pipeHandle = open_named_pipe(handle->name, &duplex_flags);
    if (pipeHandle != INVALID_HANDLE_VALUE) {
      break;
    }

    SwitchToThread();
  }