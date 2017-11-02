static CURLcode pop3_setup_connection(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;

  /* Initialise the POP3 layer */
  CURLcode result = pop3_init(conn);
  if(result)
    return result;

  if(conn->bits.httpproxy && !data->set.tunnel_thru_httpproxy) {
    /* Unless we have asked to tunnel POP3 operations through the proxy, we
       switch and use HTTP operations only */
#ifndef CURL_DISABLE_HTTP
    if(conn->handler == &Curl_handler_pop3)
      conn->handler = &Curl_handler_pop3_proxy;
    else {
#ifdef USE_SSL
      conn->handler = &Curl_handler_pop3s_proxy;
#else
      failf(data, "POP3S not supported!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    }

    /* set it up as an HTTP connection instead */
    return conn->handler->setup_connection(conn);
#else
    failf(data, "POP3 over http proxy requires HTTP support built-in!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }

  data->state.path++;   /* don't include the initial slash */

  return CURLE_OK;
}