{
    err = uv_translate_sys_error(GET_REQ_SOCK_ERROR(req));
    if (err == UV_ECONNABORTED) {
      /* use UV_ECANCELED for consistency with Unix */
      err = UV_ECANCELED;
    }
    req->cb(req, err);
  }