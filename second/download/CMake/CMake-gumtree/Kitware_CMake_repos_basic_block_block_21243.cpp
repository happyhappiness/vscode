{
    err = GET_REQ_ERROR(req);
    req->cb(req, uv_translate_sys_error(err));
  }