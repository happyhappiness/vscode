{
      CloseHandle(req->u.io.overlapped.hEvent);
      req->event_handle = NULL;
    }