CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
{
  struct negotiatedata *neg_ctx = proxy?&conn->data->state.proxyneg:
    &conn->data->state.negotiate;
  char *encoded = NULL;
  size_t len = 0;
  char *userp;
  CURLcode result;
  OM_uint32 discard_st;

  result = Curl_base64_encode(conn->data,
                              neg_ctx->output_token.value,
                              neg_ctx->output_token.length,
                              &encoded, &len);
  if(result) {
    gss_release_buffer(&discard_st, &neg_ctx->output_token);
    neg_ctx->output_token.value = NULL;
    neg_ctx->output_token.length = 0;
    return result;
  }

  if(!encoded || !len) {
    gss_release_buffer(&discard_st, &neg_ctx->output_token);
    neg_ctx->output_token.value = NULL;
    neg_ctx->output_token.length = 0;
    return CURLE_REMOTE_ACCESS_DENIED;
  }

  userp = aprintf("%sAuthorization: Negotiate %s\r\n", proxy ? "Proxy-" : "",
                  encoded)