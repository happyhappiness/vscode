{
    err = GetLastError();
    if (err == ERROR_INVALID_PARAMETER) {
      return UV_ESRCH;
    } else {
      return uv_translate_sys_error(err);
    }
  }