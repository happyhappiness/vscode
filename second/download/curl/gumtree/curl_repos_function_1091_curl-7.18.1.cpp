static CURLcode win32_init(void)
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

#if defined(ENABLE_IPV6) && (USE_WINSOCK < 2)
  Error IPV6_requires_winsock2
#endif

  wVersionRequested = MAKEWORD(USE_WINSOCK, USE_WINSOCK);

  err = WSAStartup(wVersionRequested, &wsaData);

  if(err != 0)
    /* Tell the user that we couldn't find a useable */
    /* winsock.dll.     */
    return CURLE_FAILED_INIT;

  /* Confirm that the Windows Sockets DLL supports what we need.*/
  /* Note that if the DLL supports versions greater */
  /* than wVersionRequested, it will still return */
  /* wVersionRequested in wVersion. wHighVersion contains the */
  /* highest supported version. */

  if( LOBYTE( wsaData.wVersion ) != LOBYTE(wVersionRequested) ||
       HIBYTE( wsaData.wVersion ) != HIBYTE(wVersionRequested) ) {
    /* Tell the user that we couldn't find a useable */

    /* winsock.dll. */
    WSACleanup();
    return CURLE_FAILED_INIT;
  }
  /* The Windows Sockets DLL is acceptable. Proceed. */
  return CURLE_OK;
}