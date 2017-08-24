(err == ERROR_PATH_NOT_FOUND || err == ERROR_INVALID_NAME) {
      err = WSAEACCES;  /* Translates to UV_EACCES. */
    }