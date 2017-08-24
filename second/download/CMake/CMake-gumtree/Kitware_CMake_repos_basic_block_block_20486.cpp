(!result) {
      err = GetLastError();
      return err;
    } else {
      /* Request completed immediately. */
      req->u.io.queued_bytes = 0;
    }