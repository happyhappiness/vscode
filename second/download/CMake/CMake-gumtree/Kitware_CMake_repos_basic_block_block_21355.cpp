(utf16_len == 0) {
    return uv_translate_sys_error(GetLastError());
  } else if (utf16_len > MAX_PATH) {
    return UV_EIO;
  }