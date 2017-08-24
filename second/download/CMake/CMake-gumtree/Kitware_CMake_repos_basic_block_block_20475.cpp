{
      req->event_handle = CreateEvent(NULL, 0, 0, NULL);
      if (!req->event_handle) {
        uv_fatal_error(GetLastError(), "CreateEvent");
      }
      if (!RegisterWaitForSingleObject(&req->wait_handle,
          req->u.io.overlapped.hEvent, post_completion_write_wait, (void*) req,
          INFINITE, WT_EXECUTEINWAITTHREAD)) {
        return GetLastError();
      }
    }