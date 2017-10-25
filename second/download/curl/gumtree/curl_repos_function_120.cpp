static CURLcode AllowServerConnect(struct UrlData *data,
                                   int sock)
{
  fd_set rdset;
  struct timeval dt;
  
  FD_ZERO(&rdset);

  FD_SET(sock, &rdset);

  /* we give the server 10 seconds to connect to us */
  dt.tv_sec = 10;
  dt.tv_usec = 0;

  switch ( select(sock+1, &rdset, NULL, NULL, &dt)) {
  case -1: /* error */
    /* let's die here */
    failf(data, "Error while waiting for server connect");
    return CURLE_FTP_PORT_FAILED;
  case 0:  /* timeout */
    /* let's die here */
    failf(data, "Timeout while waiting for server connect");
    return CURLE_FTP_PORT_FAILED;
  default:
    /* we have received data here */
    {
      int s;
      size_t size = sizeof(struct sockaddr_in);
      struct sockaddr_in add;

      getsockname(sock, (struct sockaddr *) &add, (int *)&size);
      s=accept(sock, (struct sockaddr *) &add, (int *)&size);

      if( -1 == s) {
	/* DIE! */
	failf(data, "Error accept()ing server connect");
	return CURLE_FTP_PORT_FAILED;
      }
      infof(data, "Connection accepted from server\n");

      data->secondarysocket = s;
    }
    break;
  }
  return CURLE_OK;
}