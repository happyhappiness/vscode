{
  int err;
  WORD wVersionRequested;
  WSADATA wsaData;

  DEBUGASSERT(data);

  /* telnet requires at least WinSock 2.0 so ask for it. */
  wVersionRequested = MAKEWORD(2, 0);

  err = WSAStartup(wVersionRequested, &wsaData);

  /* We must've called this once already, so this call */
  /* should always succeed.  But, just in case... */
  if(err != 0) {
    failf(data,"WSAStartup failed (%d)",err);
    return CURLE_FAILED_INIT;
  }

  /* We have to have a WSACleanup call for every successful */
  /* WSAStartup call. */
  WSACleanup();

  /* Check that our version is supported */
  if(LOBYTE(wsaData.wVersion) != LOBYTE(wVersionRequested) ||
      HIBYTE(wsaData.wVersion) != HIBYTE(wVersionRequested)) {
      /* Our version isn't supported */
    failf(data, "insufficient winsock version to support "
          "telnet");
    return CURLE_FAILED_INIT;
  }

  /* Our version is supported */
  return CURLE_OK;
}