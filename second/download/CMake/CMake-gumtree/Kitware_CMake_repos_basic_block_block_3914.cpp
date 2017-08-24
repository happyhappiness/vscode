{
    /* Tell the user that we couldn't find a useable */

    /* winsock.dll. */
    WSACleanup();
    return CURLE_FAILED_INIT;
  }