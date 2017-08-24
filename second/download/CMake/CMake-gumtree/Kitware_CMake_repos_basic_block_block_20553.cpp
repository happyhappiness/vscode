{
    *size = 0;
    err = uv_translate_sys_error(GetLastError());
    goto error;
  }