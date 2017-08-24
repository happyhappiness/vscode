{
  wchar_t path[MAX_PATH + 1];
  DWORD bufsize;
  size_t len;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  len = GetTempPathW(MAX_PATH + 1, path);

  if (len == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (len > MAX_PATH + 1) {
    /* This should not be possible */
    return UV_EIO;
  }

  /* The returned directory should not have a trailing slash, unless it */
  /* points at a drive root, like c:\. Remove it if needed.*/
  if (path[len - 1] == L'\\' &&
      !(len == 3 && path[1] == L':')) {
    len--;
    path[len] = L'\0';
  }

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