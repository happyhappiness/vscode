int Curl_gskit_check_cxn(struct connectdata *cxn)
{
  int err;
  int errlen;

  /* The only thing that can be tested here is at the socket level. */

  if(!cxn->ssl[FIRSTSOCKET].handle)
    return 0; /* connection has been closed */

  err = 0;
  errlen = sizeof err;

  if(getsockopt(cxn->sock[FIRSTSOCKET], SOL_SOCKET, SO_ERROR,
                 (unsigned char *) &err, &errlen) ||
     errlen != sizeof err || err)
    return 0; /* connection has been closed */

  return -1;  /* connection status unknown */
}