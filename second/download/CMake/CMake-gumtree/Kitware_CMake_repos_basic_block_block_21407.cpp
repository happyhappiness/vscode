(name_size <= 0) {
      uv__free(win_address_buf);
      uv__free(uv_address_buf);
      return uv_translate_sys_error(GetLastError());
    }