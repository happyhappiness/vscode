(!MultiByteToWideChar(CP_UTF8,
                           0,
                           path,
                           -1,
                           pathw,
                           name_size / sizeof(WCHAR))) {
    return uv_translate_sys_error(GetLastError());
  }