int Curl_input_negotiate(struct connectdata *conn, char *header)
{
  struct negotiatedata *neg_ctx = &conn->data->state.negotiate;
  OM_uint32 major_status, minor_status, minor_status2;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  int ret;
  size_t len;
  bool gss;
  const char* protocol;

  while(*header && isspace((int)*header))
    header++;
  if(checkprefix("GSS-Negotiate", header)) {
    protocol = "GSS-Negotiate";
    gss = TRUE;
  }
  else if (checkprefix("Negotiate", header)) {
    protocol = "Negotiate";
    gss = FALSE;
  }
  else
    return -1;

  if (neg_ctx->context) {
    if (neg_ctx->gss != gss) {
      return -1;
    }
  }
  else {
    neg_ctx->protocol = protocol;
    neg_ctx->gss = gss;
  }

  if (neg_ctx->context && neg_ctx->status == GSS_S_COMPLETE) {
    /* We finished succesfully our part of authentication, but server
     * rejected it (since we're again here). Exit with an error since we
     * can't invent anything better */
    Curl_cleanup_negotiate(conn->data);
    return -1;
  }

  if (neg_ctx->server_name == NULL &&
      (ret = get_gss_name(conn, &neg_ctx->server_name)))
    return ret;

  header += strlen(neg_ctx->protocol);
  while(*header && isspace((int)*header))
    header++;

  len = strlen(header);
  if (len > 0) {
    int rawlen = Curl_base64_decode(header, (unsigned char **)&input_token.value);
    if (rawlen < 0)
      return -1;
    input_token.length = rawlen;

#ifdef HAVE_SPNEGO /* Handle SPNEGO */
    if (checkprefix("Negotiate", header)) {
        ASN1_OBJECT *   object            = NULL;
        int             rc                = 1;
        unsigned char * spnegoToken       = NULL;
        size_t          spnegoTokenLength = 0;
        unsigned char * mechToken         = NULL;
        size_t          mechTokenLength   = 0;

        spnegoToken = malloc(input_token.length);
        if (input_token.value == NULL)
          return ENOMEM;
        spnegoTokenLength = input_token.length;

        object = OBJ_txt2obj ("1.2.840.113554.1.2.2", 1);
        if (!parseSpnegoTargetToken(spnegoToken,
                                    spnegoTokenLength,
                                    NULL,
                                    NULL,
                                    &mechToken,
                                    &mechTokenLength,
                                    NULL,
                                    NULL)) {
          free(spnegoToken);
          spnegoToken = NULL;
          infof(conn->data, "Parse SPNEGO Target Token failed\n");
        }
        else {
          free(input_token.value);
          input_token.value = NULL;
          input_token.value = malloc(mechTokenLength);
          memcpy(input_token.value, mechToken,mechTokenLength);
          input_token.length = mechTokenLength;
          free(mechToken);
          mechToken = NULL;
          infof(conn->data, "Parse SPNEGO Target Token succeeded\n");
        }
    }
#endif
  }

  major_status = gss_init_sec_context(&minor_status,
                                      GSS_C_NO_CREDENTIAL,
                                      &neg_ctx->context,
                                      neg_ctx->server_name,
                                      GSS_C_NO_OID,
                                      GSS_C_DELEG_FLAG,
                                      0,
                                      GSS_C_NO_CHANNEL_BINDINGS,
                                      &input_token,
                                      NULL,
                                      &output_token,
                                      NULL,
                                      NULL);
  if (input_token.length > 0)
    gss_release_buffer(&minor_status2, &input_token);
  neg_ctx->status = major_status;
  if (GSS_ERROR(major_status)) {
    /* Curl_cleanup_negotiate(conn->data) ??? */
    log_gss_error(conn, minor_status,
                  (char *)"gss_init_sec_context() failed: ");
    return -1;
  }

  if (output_token.length == 0) {
    return -1;
  }

  neg_ctx->output_token = output_token;
  /* conn->bits.close = FALSE; */

  return 0;
}