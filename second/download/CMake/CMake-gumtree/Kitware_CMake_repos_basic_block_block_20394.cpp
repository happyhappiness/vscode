{
      /* Failure */
      UNREGISTER_HANDLE_REQ(loop, handle, req);

      handle->flags |= UV_HANDLE_WRITABLE; /* Questionable */
      if (req->cb) {
        err = pRtlNtStatusToDosError(nt_status);
        req->cb(req, uv_translate_sys_error(err));
      }

      DECREASE_PENDING_REQ_COUNT(handle);
      return;
    }