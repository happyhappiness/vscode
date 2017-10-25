static void win32_init(void)
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
  wVersionRequested = MAKEWORD(2, 0);

  err = WSAStartup(wVersionRequested, &wsaData);

  if (err != 0) {
    perror("Winsock init failed");
    logmsg("Error initialising winsock -- aborting\n");
    exit(1);
  }

  if ( LOBYTE( wsaData.wVersion ) != 2 ||
       HIBYTE( wsaData.wVersion ) != 0 ) {

    WSACleanup();
    perror("Winsock init failed");
    logmsg("No suitable winsock.dll found -- aborting\n");
    exit(1);
  }
}