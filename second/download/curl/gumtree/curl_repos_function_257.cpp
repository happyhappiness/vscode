CURLcode Curl_output_negotiate(struct connectdata *conn)
{
  struct negotiatedata *neg_ctx = &conn->data->state.negotiate;
  OM_uint32 minor_status;
  char *encoded = NULL;
  int len;

#ifdef HAVE_SPNEGO /* Handle SPNEGO */
  if (checkprefix("Negotiate",neg_ctx->protocol)) {
    ASN1_OBJECT *   object            = NULL;
    int             rc                = 1;
    unsigned char * spnegoToken       = NULL;
    size_t          spnegoTokenLength = 0;
    unsigned char * responseToken       = NULL;
    size_t          responseTokenLength = 0;

    responseToken = malloc(neg_ctx->output_token.length);
    if ( responseToken == NULL)
      return CURLE_OUT_OF_MEMORY;
    memcpy(responseToken, neg_ctx->output_token.value,
           neg_ctx->output_token.length);
    responseTokenLength = neg_ctx->output_token.length;

    object=OBJ_txt2obj ("1.2.840.113554.1.2.2", 1);
    if (!makeSpnegoInitialToken (object,
                                 responseToken,
                                 responseTokenLength,
                                 &spnegoToken,
                                 &spnegoTokenLength)) {
      free(responseToken);
      responseToken = NULL;
      infof(conn->data, "Make SPNEGO Initial Token failed\n");
    }
    else {
      free(neg_ctx->output_token.value);
      responseToken = NULL;
      neg_ctx->output_token.value = malloc(spnegoTokenLength);
      memcpy(neg_ctx->output_token.value, spnegoToken,spnegoTokenLength);
      neg_ctx->output_token.length = spnegoTokenLength;
      free(spnegoToken);
      spnegoToken = NULL;
      infof(conn->data, "Make SPNEGO Initial Token succeeded\n");
    }
  }
#endif
  len = Curl_base64_encode(neg_ctx->output_token.value,
                           neg_ctx->output_token.length,
                           &encoded);

  if (len < 0)
    return CURLE_OUT_OF_MEMORY;

  conn->allocptr.userpwd =
    aprintf("Authorization: %s %s\r\n", neg_ctx->protocol, encoded);
  free(encoded);
  gss_release_buffer(&minor_status, &neg_ctx->output_token);
  return (conn->allocptr.userpwd == NULL) ? CURLE_OUT_OF_MEMORY : CURLE_OK;
}