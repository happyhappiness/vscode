(GetLastError() == ERROR_PIPE_BUSY) {
      /* Wait for the server to make a pipe instance available. */
      if (!QueueUserWorkItem(&pipe_connect_thread_proc,
                             req,
                             WT_EXECUTELONGFUNCTION)) {
        err = GetLastError();
        goto error;
      }

      REGISTER_HANDLE_REQ(loop, handle, req);
      handle->reqs_pending++;

      return;
    }