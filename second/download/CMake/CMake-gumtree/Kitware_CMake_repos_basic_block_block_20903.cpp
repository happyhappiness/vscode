{
    req->event_handle = CreateEvent(NULL, 0, 0, NULL);
    if (!req->event_handle) {
      uv_fatal_error(GetLastError(), "CreateEvent");
    }
    req->u.io.overlapped.hEvent = (HANDLE) ((ULONG_PTR) req->event_handle | 1);
    req->wait_handle = INVALID_HANDLE_VALUE;
  }