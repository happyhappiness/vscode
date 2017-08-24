{
      /* Make this req pending reporting an error. */
      SET_REQ_ERROR(req, GetLastError());
      goto error;
    }