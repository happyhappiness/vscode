(!(FillConsoleOutputCharacterW(handle->handle,
                              L'\x20',
                              count,
                              start,
                              &written) &&
        FillConsoleOutputAttribute(handle->handle,
                                   info.wAttributes,
                                   written,
                                   start,
                                   &written))) {
    if (GetLastError() == ERROR_INVALID_PARAMETER) {
      /* The console may be resized - retry */
      goto retry;
    } else {
      *error = GetLastError();
      return -1;
    }
  }