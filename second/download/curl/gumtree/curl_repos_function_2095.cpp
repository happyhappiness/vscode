int Curl_ossl_check_cxn(struct connectdata *conn)
{
  int rc;
  char buf;

  rc = SSL_peek(conn->ssl[FIRSTSOCKET].handle, (void*)&buf, 1);
  if(rc > 0)
    return 1; /* connection still in place */

  if(rc == 0)
    return 0; /* connection has been closed */

  return -1; /* connection status unknown */
}