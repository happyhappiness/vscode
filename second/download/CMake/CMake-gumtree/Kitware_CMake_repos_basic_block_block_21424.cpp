{
  uv_passwd_t pwd;
  wchar_t path[MAX_PATH];
  DWORD bufsize;
  size_t len;
  int r;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  /* Check if the USERPROFILE environment variable is set first */
  len = GetEnvironmentVariableW(L"USERPROFILE", path, MAX_PATH);

  if (len == 0) {
    r = GetLastError();

    /* Don't return an error if USERPROFILE was not found */
    if (r != ERROR_ENVVAR_NOT_FOUND)
      return uv_translate_sys_error(r);
  } else if (len > MAX_PATH) {
    /* This should not be possible */
    return UV_EIO;
  } else {
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

  /* USERPROFILE is not set, so call uv__getpwuid_r() */
  r = uv__getpwuid_r(&pwd);

  if (r != 0) {
    return r;
  }

  len = strlen(pwd.homedir);

  if (len >= *size) {
    *size = len + 1;
    uv_os_free_passwd(&pwd);
    return UV_ENOBUFS;
  }

  memcpy(buffer, pwd.homedir, len + 1);
  *size = len;
  uv_os_free_passwd(&pwd);

  return 0;
}