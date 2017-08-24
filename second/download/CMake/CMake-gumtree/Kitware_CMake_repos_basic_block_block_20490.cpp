{
      err = GetLastError();
      CloseHandle(ipc_header_req->u.io.overlapped.hEvent);
      return err;
    }