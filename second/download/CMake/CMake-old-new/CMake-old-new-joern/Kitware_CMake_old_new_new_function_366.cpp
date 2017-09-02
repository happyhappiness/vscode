CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
{
  struct negotiatedata *neg_ctx = proxy ? &conn->data->state.proxyneg :
    &conn->data->state.negotiate;
  char *base64 = NULL;
  size_t len = 0;
  char *userp;
  CURLcode result;

  result = Curl_auth_create_spnego_message(conn->data, neg_ctx, &base64, &len);
  if(result)
    return result;

  userp = aprintf("%sAuthorization: Negotiate %s\r\n", proxy ? "Proxy-" : "",
                  base64);

  if(proxy) {
    Curl_safefree(conn->allocptr.proxyuserpwd);
    conn->allocptr.proxyuserpwd = userp;
  }
  else {
    Curl_safefree(conn->allocptr.userpwd);
    conn->allocptr.userpwd = userp;
  }

  free(base64);

  return (userp == NULL) ? CURLE_OUT_OF_MEMORY : CURLE_OK;
}