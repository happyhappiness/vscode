{
  DWORD bufsize;

  if (utf16 == NULL)
    return UV_EINVAL;

  /* Check how much space we need */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                utf16,
                                utf16len,
                                NULL,
                                0,
                                NULL,
                                NULL);

  if (bufsize == 0)
    return uv_translate_sys_error(GetLastError());

  /* Allocate the destination buffer adding an extra byte for the terminating
   * NULL. If utf16len is not -1 WideCharToMultiByte will not add it, so
   * we do it ourselves always, just in case. */
  *utf8 = uv__malloc(bufsize + 1);

  if (*utf8 == NULL)
    return UV_ENOMEM;

  /* Convert to UTF-8 */
  bufsize = WideCharToMultiByte(CP_UTF8,
                                0,
                                utf16,
                                utf16len,
                                *utf8,
                                bufsize,
                                NULL,
                                NULL);

  if (bufsize == 0) {
    uv__free(*utf8);
    *utf8 = NULL;
    return uv_translate_sys_error(GetLastError());
  }

  (*utf8)[bufsize] = '\0';
  return 0;
}