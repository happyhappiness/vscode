{
  DWORD utf16_len;
  WCHAR utf16_buffer[MAX_PATH];
  int r;

  if (buffer == NULL || size == NULL) {
    return UV_EINVAL;
  }

  utf16_len = GetCurrentDirectoryW(MAX_PATH, utf16_buffer);
  if (utf16_len == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (utf16_len > MAX_PATH) {
    /* This should be impossible;  however the CRT has a code path to deal */
    /* with this scenario, so I added a check anyway. */
    return UV_EIO;
  }

  /* utf16_len contains the length, *not* including the terminating null. */
  utf16_buffer[utf16_len] = L'\0';

  /* The returned directory should not have a trailing slash, unless it */
  /* points at a drive root, like c:\. Remove it if needed.*/
  if (utf16_buffer[utf16_len - 1] == L'\\' &&
      !(utf16_len == 3 && utf16_buffer[1] == L':')) {
    utf16_len--;
    utf16_buffer[utf16_len] = L'\0';
  }

  /* Check how much space we need */
  r = WideCharToMultiByte(CP_UTF8,
                          0,
                          utf16_buffer,
                          -1,
                          NULL,
                          0,
                          NULL,
                          NULL);
  if (r == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (r > (int) *size) {
    *size = r;
    return UV_ENOBUFS;
  }

  /* Convert to UTF-8 */
  r = WideCharToMultiByte(CP_UTF8,
                          0,
                          utf16_buffer,
                          -1,
                          buffer,
                          *size > INT_MAX ? INT_MAX : (int) *size,
                          NULL,
                          NULL);
  if (r == 0) {
    return uv_translate_sys_error(GetLastError());
  }

  *size = r - 1;
  return 0;
}