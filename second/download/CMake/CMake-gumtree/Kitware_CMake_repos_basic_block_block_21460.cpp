{
  wchar_t var[MAX_ENV_VAR_LENGTH];
  wchar_t* name_w;
  DWORD bufsize;
  size_t len;
  int r;

  if (name == NULL || buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  r = uv__convert_utf8_to_utf16(name, -1, &name_w);

  if (r != 0)
    return r;

  len = GetEnvironmentVariableW(name_w, var, MAX_ENV_VAR_LENGTH);
  uv__free(name_w);
  assert(len < MAX_ENV_VAR_LENGTH); /* len does not include the null */

  if (len == 0) {
    r = GetLastError();

    if (r == ERROR_ENVVAR_NOT_FOUND)
      return UV_ENOENT;

    return uv_translate_sys_error(r);
  }

  /* Check how much space we need */
  bufsize = WideCharToMultiByte(CP_UTF8, 0, var, -1, NULL, 0, NULL, NULL);

  if (bufsize == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (bufsize > *size) {
    *size = bufsize;
    return UV_ENOBUFS;
  }

  /* Convert to UTF-8 */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                var,
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