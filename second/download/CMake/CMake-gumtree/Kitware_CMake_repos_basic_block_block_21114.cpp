{
    /* Cancel raw read */
    /* Write some bullshit event to force the console wait to return. */
    memset(&record, 0, sizeof record);
    if (!WriteConsoleInputW(handle->handle, &record, 1, &written)) {
      return GetLastError();
    }
  }