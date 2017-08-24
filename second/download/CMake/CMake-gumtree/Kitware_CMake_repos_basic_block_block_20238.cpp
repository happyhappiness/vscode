(fs__utime_handle(handle, req->fs.time.atime, req->fs.time.mtime) != 0) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    CloseHandle(handle);
    return;
  }