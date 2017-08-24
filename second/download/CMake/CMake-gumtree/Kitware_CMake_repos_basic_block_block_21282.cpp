{
      /* The req will be processed with IOCP. */
      handle->flags |= UV_HANDLE_READ_PENDING;
      handle->reqs_pending++;
    }