{
    req->u.io.overlapped.hEvent = (HANDLE) ((ULONG_PTR) req->event_handle | 1);
  }