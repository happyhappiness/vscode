static int Curl_nss_check_cxn(struct connectdata *conn)
{
  struct ssl_connect_data *connssl = &conn->ssl[FIRSTSOCKET];
  int rc;
  char buf;

  rc =
    PR_Recv(BACKEND->handle, (void *)&buf, 1, PR_MSG_PEEK,
            PR_SecondsToInterval(1));
  if(rc > 0)
    return 1; /* connection still in place */

  if(rc == 0)
    return 0; /* connection has been closed */

  return -1;  /* connection status unknown */
}