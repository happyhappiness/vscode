{
#ifdef USE_WINSOCK
  WORD wVersionRequested;
  WSADATA wsaData;
  int res;

#if defined(ENABLE_IPV6) && (USE_WINSOCK < 2)
  Error IPV6_requires_winsock2
#endif

  wVersionRequested = MAKEWORD(USE_WINSOCK, USE_WINSOCK);

  res = WSAStartup(wVersionRequested, &wsaData);

  if(res != 0)
    /* Tell the user that we couldn't find a useable */
    /* winsock.dll.     */
    return CURLE_FAILED_INIT;

  /* Confirm that the Windows Sockets DLL supports what we need.*/
  /* Note that if the DLL supports versions greater */
  /* than wVersionRequested, it will still return */
  /* wVersionRequested in wVersion. wHighVersion contains the */
  /* highest supported version. */

  if(LOBYTE(wsaData.wVersion) != LOBYTE(wVersionRequested) ||
     HIBYTE(wsaData.wVersion) != HIBYTE(wVersionRequested) ) {
    /* Tell the user that we couldn't find a useable */

    /* winsock.dll. */
    WSACleanup();
    return CURLE_FAILED_INIT;
  }
  /* The Windows Sockets DLL is acceptable. Proceed. */
#elif defined(USE_LWIPSOCK)
  lwip_init();
#endif

#ifdef USE_WINDOWS_SSPI
  {
    CURLcode result = Curl_sspi_global_init();
    if(result)
      return result;
  }
#endif

  return CURLE_OK;
}