{
    err = 0;
    if (REQ_SUCCESS(req)) {
      uv_pipe_connection_init(handle);
    } else {
      err = GET_REQ_ERROR(req);
    }
    req->cb(req, uv_translate_sys_error(err));
  }