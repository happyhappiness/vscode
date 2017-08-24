{
    r = GetLastError();
    CloseHandle(token);

    /* This should not be possible */
    if (r == ERROR_INSUFFICIENT_BUFFER)
      return UV_ENOMEM;

    return uv_translate_sys_error(r);
  }