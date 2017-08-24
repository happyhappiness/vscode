{
    r = GetLastError();

    if (r == ERROR_ENVVAR_NOT_FOUND)
      return UV_ENOENT;

    return uv_translate_sys_error(r);
  }