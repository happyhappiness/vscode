{
      req->u.io.overlapped.hEvent = (HANDLE) ((uintptr_t) req->event_handle | 1);
    }