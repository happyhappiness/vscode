CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
{
  struct negotiatedata *neg_ctx = proxy?&conn->data->state.proxyneg:
    &conn->data->state.negotiate;
  char *encoded = NULL;
  size_t len = 0;
  char *userp;
  CURLcode error;
  OM_uint32 discard_st;

#ifdef HAVE_SPNEGO /* Handle SPNEGO */
  if(checkprefix("Negotiate", neg_ctx->protocol)) {
    ASN1_OBJECT    *object              = NULL;
    unsigned char  *responseToken       = NULL;
    size_t          responseTokenLength = 0;
    gss_buffer_desc spnegoToken         = GSS_C_EMPTY_BUFFER;

    responseToken = malloc(neg_ctx->output_token.length);
    if(responseToken == NULL)
      return CURLE_OUT_OF_MEMORY;
    memcpy(responseToken, neg_ctx->output_token.value,
           neg_ctx->output_token.length);
    responseTokenLength = neg_ctx->output_token.length;

    object = OBJ_txt2obj("1.2.840.113554.1.2.2", 1);
    if(!object) {
      Curl_safefree(responseToken);
      return CURLE_OUT_OF_MEMORY;
    }

    if(!makeSpnegoInitialToken(object,
                               responseToken,
                               responseTokenLength,
                               (unsigned char**)&spnegoToken.value,
                               &spnegoToken.length)) {
      Curl_safefree(responseToken);
      ASN1_OBJECT_free(object);
      infof(conn->data, "Make SPNEGO Initial Token failed\n");
    }
    else if(!spnegoToken.value || !spnegoToken.length) {
      Curl_safefree(responseToken);
      ASN1_OBJECT_free(object);
      if(spnegoToken.value)
        gss_release_buffer(&discard_st, &spnegoToken);
      infof(conn->data, "Make SPNEGO Initial Token succeeded (NULL token)\n");
    }
    else {
      Curl_safefree(responseToken);
      ASN1_OBJECT_free(object);
      gss_release_buffer(&discard_st, &neg_ctx->output_token);
      neg_ctx->output_token.value = spnegoToken.value;
      neg_ctx->output_token.length = spnegoToken.length;
      infof(conn->data, "Make SPNEGO Initial Token succeeded\n");
    }
  }
#endif
  error = Curl_base64_encode(conn->data,
                             neg_ctx->output_token.value,
                             neg_ctx->output_token.length,
                             &encoded, &len);
  if(error) {
    gss_release_buffer(&discard_st, &neg_ctx->output_token);
    neg_ctx->output_token.value = NULL;
    neg_ctx->output_token.length = 0;
    return error;
  }

  if(!encoded || !len) {
    gss_release_buffer(&discard_st, &neg_ctx->output_token);
    neg_ctx->output_token.value = NULL;
    neg_ctx->output_token.length = 0;
    return CURLE_REMOTE_ACCESS_DENIED;
  }

  userp = aprintf("%sAuthorization: %s %s\r\n", proxy ? "Proxy-" : "",
                  neg_ctx->protocol, encoded);
  if(proxy) {
    Curl_safefree(conn->allocptr.proxyuserpwd);
    conn->allocptr.proxyuserpwd = userp;
  }
  else {
    Curl_safefree(conn->allocptr.userpwd);
    conn->allocptr.userpwd = userp;
  }

  Curl_safefree(encoded);
  Curl_cleanup_negotiate(conn->data);

  return (userp == NULL) ? CURLE_OUT_OF_MEMORY : CURLE_OK;
}