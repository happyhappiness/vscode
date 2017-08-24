(handle->delayed_error) {
    return uv_translate_sys_error(handle->delayed_error);
  }