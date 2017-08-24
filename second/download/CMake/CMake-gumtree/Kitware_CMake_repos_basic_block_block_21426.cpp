{
    /* Check how much space we need */
    bufsize = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);

    if (bufsize == 0) {
      return uv_translate_sys_error(GetLastError());
    } else if (bufsize > *size) {
      *size = bufsize;
      return UV_ENOBUFS;
    }

    /* Convert to UTF-8 */
    bufsize = WideCharToMultiByte(CP_UTF8,
                                  0,
                                  path,
                                  -1,
                                  buffer,
                                  *size,
                                  NULL,
                                  NULL);

    if (bufsize == 0)
      return uv_translate_sys_error(GetLastError());

    *size = bufsize - 1;
    return 0;
  }