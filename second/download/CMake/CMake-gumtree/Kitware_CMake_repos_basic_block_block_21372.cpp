{
  size_t len;

  if (buffer == NULL || size == 0)
    return UV_EINVAL;

  uv__once_init();

  EnterCriticalSection(&process_title_lock);
  /*
   * If the process_title was never read before nor explicitly set,
   * we must query it with getConsoleTitleW
   */
  if (!process_title && uv__get_process_title() == -1) {
    LeaveCriticalSection(&process_title_lock);
    return uv_translate_sys_error(GetLastError());
  }

  assert(process_title);
  len = strlen(process_title) + 1;

  if (size < len) {
    LeaveCriticalSection(&process_title_lock);
    return UV_ENOBUFS;
  }

  memcpy(buffer, process_title, len);
  LeaveCriticalSection(&process_title_lock);

  return 0;
}