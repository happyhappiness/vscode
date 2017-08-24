(CreateIoCompletionPort(pipeHandle,
                               loop->iocp,
                               (ULONG_PTR)handle,
                               0) == NULL) {
      handle->flags |= UV_HANDLE_EMULATE_IOCP;
    }