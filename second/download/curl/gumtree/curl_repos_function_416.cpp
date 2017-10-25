static bool
ConnectionExists(struct SessionHandle *data,
                 struct connectdata *needle,
                 struct connectdata **usethis)
{
  long i;
  struct connectdata *check;

  for(i=0; i< data->state.numconnects; i++) {
    bool match = FALSE;
    /*
     * Note that if we use a HTTP proxy, we check connections to that
     * proxy and not to the actual remote server.
     */
    check = data->state.connects[i];
    if(!check)
      /* NULL pointer means not filled-in entry */
      continue;

    if((needle->protocol&PROT_SSL) != (check->protocol&PROT_SSL))
      /* don't do mixed SSL and non-SSL connections */
      continue;

    if(!needle->bits.httpproxy || needle->protocol&PROT_SSL) {
      /* The requested connection does not use a HTTP proxy or it
         uses SSL. */

      if(!(needle->protocol&PROT_SSL) && check->bits.httpproxy)
        /* we don't do SSL but the cached connection has a proxy,
           then don't match this */
        continue;

      if(strequal(needle->protostr, check->protostr) &&
         strequal(needle->host.name, check->host.name) &&
         (needle->remote_port == check->remote_port) ) {
        if(needle->protocol & PROT_SSL) {
          /* This is SSL, verify that we're using the same
             ssl options as well */
          if(!Curl_ssl_config_matches(&needle->ssl_config,
                                      &check->ssl_config)) {
            continue;
          }
        }
        if((needle->protocol & PROT_FTP) ||
           ((needle->protocol & PROT_HTTP) &&
            (needle->data->state.authhost.want==CURLAUTH_NTLM))) {
          /* This is FTP or HTTP+NTLM, verify that we're using the same name
             and password as well */
          if(!strequal(needle->user, check->user) ||
             !strequal(needle->passwd, check->passwd)) {
            /* one of them was different */
            continue;
          }
        }
        match = TRUE;
      }
    }
    else { /* The requested needle connection is using a proxy,
              is the checked one using the same? */
      if(check->bits.httpproxy &&
         strequal(needle->proxy.name, check->proxy.name) &&
         needle->port == check->port) {
        /* This is the same proxy connection, use it! */
        match = TRUE;
      }
    }

    if(match) {
      bool dead = SocketIsDead(check->sock[FIRSTSOCKET]);
      if(dead) {
        /*
         */
        infof(data, "Connection %d seems to be dead!\n", i);
        Curl_disconnect(check); /* disconnect resources */
        data->state.connects[i]=NULL; /* nothing here */

        /* There's no need to continue searching, because we only store
           one connection for each unique set of identifiers */
        return FALSE;
      }

      *usethis = check;
      return TRUE; /* yes, we found one to use! */
    }
  }
  return FALSE; /* no matching connecting exists */
}