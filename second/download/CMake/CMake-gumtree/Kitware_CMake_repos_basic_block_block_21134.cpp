(GetLastError() == ERROR_INVALID_PARAMETER) {
      /* The console may be resized - retry */
      goto retry;
    } else {
      *error = GetLastError();
      return -1;
    }