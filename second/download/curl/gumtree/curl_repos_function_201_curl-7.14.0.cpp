static
int waitconnect(curl_socket_t sockfd, /* socket */
                long timeout_msec)
{
  int rc;
#ifdef mpeix
  /* Call this function once now, and ignore the results. We do this to
     "clear" the error state on the socket so that we can later read it
     reliably. This is reported necessary on the MPE/iX operating system. */
  verifyconnect(sockfd, NULL);
#endif

  /* now select() until we get connect or timeout */
  rc = Curl_select(CURL_SOCKET_BAD, sockfd, (int)timeout_msec);
  if(-1 == rc)
    /* error, no connect here, try next */
    return WAITCONN_SELECT_ERROR;

  else if(0 == rc)
    /* timeout, no connect today */
    return WAITCONN_TIMEOUT;

  if(rc & CSELECT_ERR)
    /* error condition caught */
    return WAITCONN_FDSET_ERROR;

  /* we have a connect! */
  return WAITCONN_CONNECTED;
}