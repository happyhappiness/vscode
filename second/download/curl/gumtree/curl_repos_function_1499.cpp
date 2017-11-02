CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
{
  struct negotiatedata *neg_ctx = proxy?&conn->data->state.proxyneg:
    &conn->data->state.negotiate;
  char *encoded = NULL;
  size_t len = 0;
  char *userp;
  CURLcode error;

  error = Curl_base64_encode(conn->data,
                             (const char*)neg_ctx->output_token,
                             neg_ctx->output_token_length,
                             &encoded, &len);
  if(error)
    return error;

  if(!len)
    return CURLE_REMOTE_ACCESS_DENIED;

  userp = aprintf("%sAuthorization: Negotiate %s\r\n", proxy ? "Proxy-" : "",
                  encoded);

  if(proxy) {
    Curl_safefree(conn->allocptr.proxyuserpwd);
    conn->allocptr.proxyuserpwd = userp;
  }
  else {
    Curl_safefree(conn->allocptr.userpwd);
    conn->allocptr.userpwd = userp;
  }
  free(encoded);
  return (userp == NULL) ? CURLE_OUT_OF_MEMORY : CURLE_OK;
}