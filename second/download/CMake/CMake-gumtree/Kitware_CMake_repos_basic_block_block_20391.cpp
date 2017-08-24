{
        err = GetLastError();
        req->cb(req, uv_translate_sys_error(err));
      }