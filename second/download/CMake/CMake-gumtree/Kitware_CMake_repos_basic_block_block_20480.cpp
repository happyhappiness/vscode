{
      err = GetLastError();
      CloseHandle(req->u.io.overlapped.hEvent);
      return err;
    }