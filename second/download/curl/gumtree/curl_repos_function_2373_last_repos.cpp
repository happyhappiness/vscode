static void ossl_close(struct ssl_connect_data *connssl)
{
  if(BACKEND->handle) {
    (void)SSL_shutdown(BACKEND->handle);
    SSL_set_connect_state(BACKEND->handle);

    SSL_free(BACKEND->handle);
    BACKEND->handle = NULL;
  }
  if(BACKEND->ctx) {
    SSL_CTX_free(BACKEND->ctx);
    BACKEND->ctx = NULL;
  }
}