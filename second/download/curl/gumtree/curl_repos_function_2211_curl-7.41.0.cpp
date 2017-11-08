void Curl_cyassl_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *conssl = &conn->ssl[sockindex];

  if(conssl->handle) {
    (void)SSL_shutdown(conssl->handle);
    SSL_free (conssl->handle);
    conssl->handle = NULL;
  }
  if(conssl->ctx) {
    SSL_CTX_free (conssl->ctx);
    conssl->ctx = NULL;
  }
}