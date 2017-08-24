(req->wait_handle == INVALID_HANDLE_VALUE) {
        if (!RegisterWaitForSingleObject(&req->wait_handle,
            req->u.io.overlapped.hEvent, post_completion_read_wait, (void*) req,
            INFINITE, WT_EXECUTEINWAITTHREAD)) {
          SET_REQ_ERROR(req, GetLastError());
          goto error;
        }
      }