static void nss_close(struct ssl_connect_data *connssl)
{
  /* before the cleanup, check whether we are using a client certificate */
  const bool client_cert = (BACKEND->client_nickname != NULL)
    || (BACKEND->obj_clicert != NULL);

  free(BACKEND->client_nickname);
  BACKEND->client_nickname = NULL;

  /* destroy all NSS objects in order to avoid failure of NSS shutdown */
  Curl_llist_destroy(&BACKEND->obj_list, NULL);
  BACKEND->obj_clicert = NULL;

  if(BACKEND->handle) {
    if(client_cert)
      /* A server might require different authentication based on the
       * particular path being requested by the client.  To support this
       * scenario, we must ensure that a connection will never reuse the
       * authentication data from a previous connection. */
      SSL_InvalidateSession(BACKEND->handle);

    PR_Close(BACKEND->handle);
    BACKEND->handle = NULL;
  }
}