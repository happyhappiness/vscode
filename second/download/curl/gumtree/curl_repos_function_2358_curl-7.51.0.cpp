static void free_ssl_structs(struct ssl_connect_data *connssl)
{
  if(connssl->ssl) {
    ssl_free (connssl->ssl);
    connssl->ssl = NULL;
  }
  if(connssl->ssl_ctx) {
    ssl_ctx_free(connssl->ssl_ctx);
    connssl->ssl_ctx = NULL;
  }
}