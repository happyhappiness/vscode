static void free_ssl_structs(struct ssl_connect_data *connssl)
{
  if(BACKEND->ssl) {
    ssl_free(BACKEND->ssl);
    BACKEND->ssl = NULL;
  }
  if(BACKEND->ssl_ctx) {
    ssl_ctx_free(BACKEND->ssl_ctx);
    BACKEND->ssl_ctx = NULL;
  }
}