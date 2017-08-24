(!(FillConsoleOutputCharacterW(handle->handle,
                                    L'\x20',
                                    count,
                                    origin,
                                    &written) &&
        FillConsoleOutputAttribute(handle->handle,
                                   char_attrs,
                                   written,
                                   origin,
                                   &written))) {
    if (GetLastError() == ERROR_INVALID_PARAMETER) {
      /* The console may be resized - retry */
      goto retry;
    } else {
      *error = GetLastError();
      return -1;
    }
  }