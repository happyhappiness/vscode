CURLcode Curl_input_negotiate(struct connectdata *conn, bool proxy,
                              const char *header)
{
  struct SessionHandle *data = conn->data;
  struct negotiatedata *neg_ctx = proxy?&data->state.proxyneg:
    &data->state.negotiate;
  OM_uint32 major_status, minor_status, discard_st;
  gss_buffer_desc spn_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  size_t len;
  size_t rawlen = 0;
  CURLcode result;

  if(neg_ctx->context && neg_ctx->status == GSS_S_COMPLETE) {
    /* We finished successfully our part of authentication, but server
     * rejected it (since we're again here). Exit with an error since we
     * can't invent anything better */
    Curl_cleanup_negotiate(data);
    return CURLE_LOGIN_DENIED;
  }

  if(!neg_ctx->server_name) {
    /* Generate our SPN */
    char *spn = Curl_sasl_build_gssapi_spn("HTTP", proxy ? conn->proxy.name :
                                                           conn->host.name);
    if(!spn)
      return CURLE_OUT_OF_MEMORY;

    /* Populate the SPN structure */
    spn_token.value = spn;
    spn_token.length = strlen(spn);

    /* Import the SPN */
    major_status = gss_import_name(&minor_status, &spn_token,
                                   GSS_C_NT_HOSTBASED_SERVICE,
                                   &neg_ctx->server_name);
    if(GSS_ERROR(major_status)) {
      Curl_gss_log_error(data, minor_status, "gss_import_name() failed: ");

      Curl_safefree(spn);

      return CURLE_OUT_OF_MEMORY;
    }

      Curl_safefree(spn);
  }

  header += strlen("Negotiate");
  while(*header && ISSPACE(*header))
    header++;

  len = strlen(header);
  if(len > 0) {
    result = Curl_base64_decode(header, (unsigned char **)&input_token.value,
                                &rawlen);
    if(result)
      return result;

    if(!rawlen) {
      infof(data, "Negotiate handshake failure (empty challenge message)\n");

      return CURLE_BAD_CONTENT_ENCODING;
    }

    input_token.length = rawlen;

    DEBUGASSERT(input_token.value != NULL);
  }

  major_status = Curl_gss_init_sec_context(data,
                                           &minor_status,
                                           &neg_ctx->context,
                                           neg_ctx->server_name,
                                           &Curl_spnego_mech_oid,
                                           GSS_C_NO_CHANNEL_BINDINGS,
                                           &input_token,
                                           &output_token,
                                           TRUE,
                                           NULL);
  Curl_safefree(input_token.value);

  neg_ctx->status = major_status;
  if(GSS_ERROR(major_status)) {
    if(output_token.value)
      gss_release_buffer(&discard_st, &output_token);
    Curl_gss_log_error(conn->data, minor_status,
                       "gss_init_sec_context() failed: ");
    return CURLE_OUT_OF_MEMORY;
  }

  if(!output_token.value || !output_token.length) {
    if(output_token.value)
      gss_release_buffer(&discard_st, &output_token);
    return CURLE_OUT_OF_MEMORY;
  }

  neg_ctx->output_token = output_token;

  return CURLE_OK;
}