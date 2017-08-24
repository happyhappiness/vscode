(!process_title && uv__get_process_title() == -1) {
    LeaveCriticalSection(&process_title_lock);
    return uv_translate_sys_error(GetLastError());
  }