{
    failf(data, "failed to find WSACreateEvent function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }