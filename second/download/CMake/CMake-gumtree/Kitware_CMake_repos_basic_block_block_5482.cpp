{
  struct Curl_easy *data = conn->data;
  CURLcode result;

  /* Clear the TLS upgraded flag */
  conn->tls_upgraded = FALSE;

  /* Set up the proxy if necessary */
  if(conn->bits.httpproxy && !data->set.tunnel_thru_httpproxy) {
    /* Unless we have asked to tunnel SMTP operations through the proxy, we
       switch and use HTTP operations only */
#ifndef CURL_DISABLE_HTTP
    if(conn->handler == &Curl_handler_smtp)
      conn->handler = &Curl_handler_smtp_proxy;
    else {
#ifdef USE_SSL
      conn->handler = &Curl_handler_smtps_proxy;
#else
      failf(data, "SMTPS not supported!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    }
    /* set it up as a HTTP connection instead */
    return conn->handler->setup_connection(conn);

#else
    failf(data, "SMTP over http proxy requires HTTP support built-in!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }

  /* Initialise the SMTP layer */
  result = smtp_init(conn);
  if(result)
    return result;

  data->state.path++;   /* don't include the initial slash */

  return CURLE_OK;
}