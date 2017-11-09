static void Curl_axtls_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  infof(conn->data, "  Curl_axtls_close\n");

    /* line from openssl.c: (void)SSL_shutdown(BACKEND->ssl);
       axTLS compat layer does nothing for SSL_shutdown */

    /* The following line is from openssl.c.  There seems to be no axTLS
       equivalent.  ssl_free and ssl_ctx_free close things.
       SSL_set_connect_state(connssl->handle); */

  free_ssl_structs(connssl);
}