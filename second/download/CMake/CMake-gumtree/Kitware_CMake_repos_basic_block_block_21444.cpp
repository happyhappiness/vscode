{
  int bufsize;

  if (utf8 == NULL)
    return UV_EINVAL;

  /* Check how much space we need */
  bufsize = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8len, NULL, 0);

  if (bufsize == 0)
    return uv_translate_sys_error(GetLastError());

  /* Allocate the destination buffer adding an extra byte for the terminating
   * NULL. If utf8len is not -1 MultiByteToWideChar will not add it, so
   * we do it ourselves always, just in case. */
  *utf16 = uv__malloc(sizeof(WCHAR) * (bufsize + 1));

  if (*utf16 == NULL)
    return UV_ENOMEM;

  /* Convert to UTF-16 */
  bufsize = MultiByteToWideChar(CP_UTF8, 0, utf8, utf8len, *utf16, bufsize);

  if (bufsize == 0) {
    uv__free(*utf16);
    *utf16 = NULL;
    return uv_translate_sys_error(GetLastError());
  }

  (*utf16)[bufsize] = '\0';
  return 0;
}