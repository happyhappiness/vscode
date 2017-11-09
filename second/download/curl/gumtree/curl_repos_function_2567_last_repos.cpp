CURLcode Curl_ssl_addsessionid(struct connectdata *conn,
                               void *ssl_sessionid,
                               size_t idsize,
                               int sockindex)
{
  size_t i;
  struct Curl_easy *data = conn->data; /* the mother of all structs */
  struct curl_ssl_session *store = &data->state.session[0];
  long oldest_age = data->state.session[0].age; /* zero if unused */
  char *clone_host;
  char *clone_conn_to_host;
  int conn_to_port;
  long *general_age;
  const bool isProxy = CONNECT_PROXY_SSL();
  struct ssl_primary_config * const ssl_config = isProxy ?
    &conn->proxy_ssl_config :
    &conn->ssl_config;

  DEBUGASSERT(SSL_SET_OPTION(primary.sessionid));

  clone_host = strdup(isProxy ? conn->http_proxy.host.name : conn->host.name);
  if(!clone_host)
    return CURLE_OUT_OF_MEMORY; /* bail out */

  if(conn->bits.conn_to_host) {
    clone_conn_to_host = strdup(conn->conn_to_host.name);
    if(!clone_conn_to_host) {
      free(clone_host);
      return CURLE_OUT_OF_MEMORY; /* bail out */
    }
  }
  else
    clone_conn_to_host = NULL;

  if(conn->bits.conn_to_port)
    conn_to_port = conn->conn_to_port;
  else
    conn_to_port = -1;

  /* Now we should add the session ID and the host name to the cache, (remove
     the oldest if necessary) */

  /* If using shared SSL session, lock! */
  if(SSLSESSION_SHARED(data)) {
    general_age = &data->share->sessionage;
  }
  else {
    general_age = &data->state.sessionage;
  }

  /* find an empty slot for us, or find the oldest */
  for(i = 1; (i < data->set.general_ssl.max_ssl_sessions) &&
        data->state.session[i].sessionid; i++) {
    if(data->state.session[i].age < oldest_age) {
      oldest_age = data->state.session[i].age;
      store = &data->state.session[i];
    }
  }
  if(i == data->set.general_ssl.max_ssl_sessions)
    /* cache is full, we must "kill" the oldest entry! */
    Curl_ssl_kill_session(store);
  else
    store = &data->state.session[i]; /* use this slot */

  /* now init the session struct wisely */
  store->sessionid = ssl_sessionid;
  store->idsize = idsize;
  store->age = *general_age;    /* set current age */
  /* free it if there's one already present */
  free(store->name);
  free(store->conn_to_host);
  store->name = clone_host;               /* clone host name */
  store->conn_to_host = clone_conn_to_host; /* clone connect to host name */
  store->conn_to_port = conn_to_port; /* connect to port number */
  /* port number */
  store->remote_port = isProxy ? (int)conn->port : conn->remote_port;
  store->scheme = conn->handler->scheme;

  if(!Curl_clone_primary_ssl_config(ssl_config, &store->ssl_config)) {
    store->sessionid = NULL; /* let caller free sessionid */
    free(clone_host);
    free(clone_conn_to_host);
    return CURLE_OUT_OF_MEMORY;
  }

  return CURLE_OK;
}