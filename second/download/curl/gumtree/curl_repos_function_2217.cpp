int Curl_cyassl_shutdown(struct connectdata *conn, int sockindex)
{
  int retval = 0;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(connssl->handle) {
    SSL_free (connssl->handle);
    connssl->handle = NULL;
  }
  return retval;
}