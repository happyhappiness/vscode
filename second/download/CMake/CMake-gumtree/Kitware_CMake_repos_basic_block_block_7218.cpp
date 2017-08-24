{
  struct curl_ssl_session *check;
  struct Curl_easy *data = conn->data;
  size_t i;
  long *general_age;
  bool no_match = TRUE;

  const bool isProxy = CONNECT_PROXY_SSL();
  struct ssl_primary_config * const ssl_config = isProxy ?
    &conn->proxy_ssl_config :
    &conn->ssl_config;
  const char * const name = isProxy ? conn->http_proxy.host.name :
    conn->host.name;
  int port = isProxy ? (int)conn->port : conn->remote_port;
  *ssl_sessionid = NULL;

  DEBUGASSERT(SSL_SET_OPTION(primary.sessionid));

  if(!SSL_SET_OPTION(primary.sessionid))
    /* session ID re-use is disabled */
    return TRUE;

  /* Lock if shared */
  if(SSLSESSION_SHARED(data))
    general_age = &data->share->sessionage;
  else
    general_age = &data->state.sessionage;

  for(i = 0; i < data->set.general_ssl.max_ssl_sessions; i++) {
    check = &data->state.session[i];
    if(!check->sessionid)
      /* not session ID means blank entry */
      continue;
    if(strcasecompare(name, check->name) &&
       ((!conn->bits.conn_to_host && !check->conn_to_host) ||
        (conn->bits.conn_to_host && check->conn_to_host &&
         strcasecompare(conn->conn_to_host.name, check->conn_to_host))) &&
       ((!conn->bits.conn_to_port && check->conn_to_port == -1) ||
        (conn->bits.conn_to_port && check->conn_to_port != -1 &&
         conn->conn_to_port == check->conn_to_port)) &&
       (port == check->remote_port) &&
       strcasecompare(conn->handler->scheme, check->scheme) &&
       Curl_ssl_config_matches(ssl_config, &check->ssl_config)) {
      /* yes, we have a session ID! */
      (*general_age)++;          /* increase general age */
      check->age = *general_age; /* set this as used in this age */
      *ssl_sessionid = check->sessionid;
      if(idsize)
        *idsize = check->idsize;
      no_match = FALSE;
      break;
    }
  }

  return no_match;
}