{
  int err;
  int length;
  WCHAR* title_w = NULL;

  uv__once_init();

  /* Find out how big the buffer for the wide-char title must be */
  length = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
  if (!length) {
    err = GetLastError();
    goto done;
  }

  /* Convert to wide-char string */
  title_w = (WCHAR*)uv__malloc(sizeof(WCHAR) * length);
  if (!title_w) {
    uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
  }

  length = MultiByteToWideChar(CP_UTF8, 0, title, -1, title_w, length);
  if (!length) {
    err = GetLastError();
    goto done;
  }

  /* If the title must be truncated insert a \0 terminator there */
  if (length > MAX_TITLE_LENGTH) {
    title_w[MAX_TITLE_LENGTH - 1] = L'\0';
  }

  if (!SetConsoleTitleW(title_w)) {
    err = GetLastError();
    goto done;
  }

  EnterCriticalSection(&process_title_lock);
  uv__free(process_title);
  process_title = uv__strdup(title);
  LeaveCriticalSection(&process_title_lock);

  err = 0;

done:
  uv__free(title_w);
  return uv_translate_sys_error(err);
}