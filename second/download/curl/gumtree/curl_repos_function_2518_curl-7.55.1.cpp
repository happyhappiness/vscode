static void nss_close(struct ssl_connect_data *connssl)
{
  /* before the cleanup, check whether we are using a client certificate */
  const bool client_cert = (connssl->client_nickname != NULL)
    || (connssl->obj_clicert != NULL);

  free(connssl->client_nickname);
  connssl->client_nickname = NULL;

  /* destroy all NSS objects in order to avoid failure of NSS shutdown */
  Curl_llist_destroy(&connssl->obj_list, NULL);
  connssl->obj_clicert = NULL;

  if(connssl->handle) {
    if(client_cert)
      /* A server might require different authentication based on the
       * particular path being requested by the client.  To support this
       * scenario, we must ensure that a connection will never reuse the
       * authentication data from a previous connection. */
      SSL_InvalidateSession(connssl->handle);

    PR_Close(connssl->handle);
    connssl->handle = NULL;
  }
}