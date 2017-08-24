(error == ERROR_INSUFFICIENT_BUFFER) {
      return UV_ENAMETOOLONG;
    } else {
      return uv_translate_sys_error(error);
    }