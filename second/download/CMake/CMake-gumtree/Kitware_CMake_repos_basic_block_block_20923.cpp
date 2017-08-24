(req->event_handle) {
      CloseHandle(req->event_handle);
      req->event_handle = NULL;
    }