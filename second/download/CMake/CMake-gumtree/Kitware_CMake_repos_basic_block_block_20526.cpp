(req->wait_handle != INVALID_HANDLE_VALUE) {
      UnregisterWait(req->wait_handle);
      req->wait_handle = INVALID_HANDLE_VALUE;
    }