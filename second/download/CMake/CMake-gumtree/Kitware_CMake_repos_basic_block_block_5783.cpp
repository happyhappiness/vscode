{
    failf(data, "failed to load WS2_32.DLL (%d)", ERRNO);
    return CURLE_FAILED_INIT;
  }