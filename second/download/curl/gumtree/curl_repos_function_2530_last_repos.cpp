static int Curl_cyassl_shutdown(struct connectdata *conn, int sockindex)
{
  int retval = 0;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(BACKEND->handle) {
    SSL_free(BACKEND->handle);
    BACKEND->handle = NULL;
  }
  return retval;
}