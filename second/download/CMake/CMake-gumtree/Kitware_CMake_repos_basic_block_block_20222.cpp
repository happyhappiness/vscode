(fs__stat_handle(handle, &req->statbuf) != 0) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }