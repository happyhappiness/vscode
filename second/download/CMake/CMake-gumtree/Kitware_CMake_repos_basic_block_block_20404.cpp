{
    err = GetLastError();
    if (err == ERROR_ACCESS_DENIED) {
      err = WSAEADDRINUSE;  /* Translates to UV_EADDRINUSE. */
    } else if (err == ERROR_PATH_NOT_FOUND || err == ERROR_INVALID_NAME) {
      err = WSAEACCES;  /* Translates to UV_EACCES. */
    }
    goto error;
  }