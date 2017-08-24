{
        err = pRtlNtStatusToDosError(nt_status);
        req->cb(req, uv_translate_sys_error(err));
      }