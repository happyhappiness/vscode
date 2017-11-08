CURLcode Curl_input_negotiate(struct connectdata *conn, bool proxy,
                              const char *header)
{
  CURLcode result;
  struct Curl_easy *data = conn->data;
  size_t len;

  /* Point to the username, password, service and host */
  const char *userp;
  const char *passwdp;
  const char *service;
  const char *host;

  /* Point to the correct struct with this */
  struct negotiatedata *neg_ctx;

  if(proxy) {
    userp = conn->http_proxy.user;
    passwdp = conn->http_proxy.passwd;
    service = data->set.str[STRING_PROXY_SERVICE_NAME] ?
              data->set.str[STRING_PROXY_SERVICE_NAME] : "HTTP";
    host = conn->http_proxy.host.name;
    neg_ctx = &data->state.proxyneg;
  }
  else {
    userp = conn->user;
    passwdp = conn->passwd;
    service = data->set.str[STRING_SERVICE_NAME] ?
              data->set.str[STRING_SERVICE_NAME] : "HTTP";
    host = conn->host.name;
    neg_ctx = &data->state.negotiate;
  }

  /* Not set means empty */
  if(!userp)
    userp = "";

  if(!passwdp)
    passwdp = "";

  /* Obtain the input token, if any */
  header += strlen("Negotiate");
  while(*header && ISSPACE(*header))
    header++;

  len = strlen(header);
  if(!len) {
    /* Is this the first call in a new negotiation? */
    if(neg_ctx->context) {
      /* The server rejected our authentication and hasn't suppled any more
      negotiation mechanisms */
      return CURLE_LOGIN_DENIED;
    }
  }

  /* Initilise the security context and decode our challenge */
  result = Curl_auth_decode_spnego_message(data, userp, passwdp, service,
                                           host, header, neg_ctx);

  if(result)
    Curl_auth_spnego_cleanup(neg_ctx);

  return result;
}