f(event_select_func == NULL) {
    failf(data, "failed to find WSAEventSelect function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }