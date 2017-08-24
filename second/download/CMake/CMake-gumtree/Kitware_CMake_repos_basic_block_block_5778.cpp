{
    failf(data, "WSACreateEvent failed (%d)", SOCKERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }