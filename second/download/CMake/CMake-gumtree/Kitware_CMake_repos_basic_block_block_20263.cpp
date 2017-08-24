(fs__realpath_handle(handle, (char**) &req->ptr) == -1) {
    CloseHandle(handle);
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }