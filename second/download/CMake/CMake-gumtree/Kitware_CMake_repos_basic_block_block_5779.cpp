{
    failf(data, "failed to find WSAEnumNetworkEvents function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }