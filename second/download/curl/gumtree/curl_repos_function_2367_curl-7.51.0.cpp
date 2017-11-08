int Curl_axtls_check_cxn(struct connectdata *conn)
{
  /* openssl.c line: rc = SSL_peek(conn->ssl[FIRSTSOCKET].ssl, (void*)&buf, 1);
     axTLS compat layer always returns the last argument, so connection is
     always alive? */

  infof(conn->data, "  Curl_axtls_check_cxn\n");
   return 1; /* connection still in place */
}