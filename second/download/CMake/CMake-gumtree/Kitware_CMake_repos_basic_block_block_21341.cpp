{
  int utf8_len, utf16_buffer_len, utf16_len;
  WCHAR* utf16_buffer;
  int err;

  if (buffer == NULL || size_ptr == NULL || *size_ptr == 0) {
    return UV_EINVAL;
  }

  if (*size_ptr > 32768) {
    /* Windows paths can never be longer than this. */
    utf16_buffer_len = 32768;
  } else {
    utf16_buffer_len = (int) *size_ptr;
  }

  utf16_buffer = (WCHAR*) uv__malloc(sizeof(WCHAR) * utf16_buffer_len);
  if (!utf16_buffer) {
    return UV_ENOMEM;
  }

  /* Get the path as UTF-16. */
  utf16_len = GetModuleFileNameW(NULL, utf16_buffer, utf16_buffer_len);
  if (utf16_len <= 0) {
    err = GetLastError();
    goto error;
  }

  /* utf16_len contains the length, *not* including the terminating null. */
  utf16_buffer[utf16_len] = L'\0';

  /* Convert to UTF-8 */
  utf8_len = WideCharToMultiByte(CP_UTF8,
                                 0,
                                 utf16_buffer,
                                 -1,
                                 buffer,
                                 (int) *size_ptr,
                                 NULL,
                                 NULL);
  if (utf8_len == 0) {
    err = GetLastError();
    goto error;
  }

  uv__free(utf16_buffer);

  /* utf8_len *does* include the terminating null at this point, but the */
  /* returned size shouldn't. */
  *size_ptr = utf8_len - 1;
  return 0;

 error:
  uv__free(utf16_buffer);
  return uv_translate_sys_error(err);
}