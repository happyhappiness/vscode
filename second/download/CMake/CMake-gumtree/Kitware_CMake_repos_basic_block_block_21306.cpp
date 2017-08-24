{
    err = 0;
    if (!REQ_SUCCESS(req)) {
      err = GET_REQ_SOCK_ERROR(req);
    }
    req->cb(req, uv_translate_sys_error(err));
  }