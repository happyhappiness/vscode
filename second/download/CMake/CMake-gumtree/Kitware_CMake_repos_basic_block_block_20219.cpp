(fs__stat_handle(handle, &req->statbuf) != 0) {
    DWORD error = GetLastError();
    if (do_lstat && error == ERROR_SYMLINK_NOT_SUPPORTED) {
      /* We opened a reparse point but it was not a symlink. Try again. */
      fs__stat_impl(req, 0);

    } else {
      /* Stat failed. */
      SET_REQ_WIN32_ERROR(req, GetLastError());
    }

    CloseHandle(handle);
    return;
  }