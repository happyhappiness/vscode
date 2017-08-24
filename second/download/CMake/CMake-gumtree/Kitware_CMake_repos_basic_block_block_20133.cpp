{
    err = GET_REQ_ERROR(req);
    handle->cb(handle, NULL, 0, uv_translate_sys_error(err));
  }