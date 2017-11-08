static void ossl_close(struct ssl_connect_data *connssl)
{
  if(connssl->handle) {
    (void)SSL_shutdown(connssl->handle);
    SSL_set_connect_state(connssl->handle);

    SSL_free(connssl->handle);
    connssl->handle = NULL;
  }
  if(connssl->ctx) {
    SSL_CTX_free(connssl->ctx);
    connssl->ctx = NULL;
  }
}