CURLcode Curl_sasl_create_gssapi_user_message(struct SessionHandle *data,
                                              const char *userp,
                                              const char *passwdp,
                                              const char *service,
                                              const bool mutual_auth,
                                              const char *chlg64,
                                              struct kerberos5data *krb5,
                                              char **outptr, size_t *outlen)
{
  CURLcode result = CURLE_OK;
  size_t chlglen = 0;
  unsigned char *chlg = NULL;
  OM_uint32 gss_status;
  OM_uint32 gss_major_status;
  OM_uint32 gss_minor_status;
  gss_buffer_desc spn_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;

  (void) userp;
  (void) passwdp;

  if(krb5->context == GSS_C_NO_CONTEXT) {
    /* Generate our SPN */
    char *spn = Curl_sasl_build_gssapi_spn(service,
                                           data->easy_conn->host.name);
    if(!spn)
      return CURLE_OUT_OF_MEMORY;

    /* Populate the SPN structure */
    spn_token.value = spn;
    spn_token.length = strlen(spn);

    /* Import the SPN */
    gss_major_status = gss_import_name(&gss_minor_status, &spn_token,
                                       GSS_C_NT_HOSTBASED_SERVICE, &krb5->spn);
    if(GSS_ERROR(gss_major_status)) {
      Curl_gss_log_error(data, gss_minor_status, "gss_import_name() failed: ");

      Curl_safefree(spn);

      return CURLE_OUT_OF_MEMORY;
    }

    Curl_safefree(spn);
  }
  else {
    /* Decode the base-64 encoded challenge message */
    if(strlen(chlg64) && *chlg64 != '=') {
      result = Curl_base64_decode(chlg64, &chlg, &chlglen);
      if(result)
        return result;
    }

    /* Ensure we have a valid challenge message */
    if(!chlg) {
      infof(data, "GSSAPI handshake failure (empty challenge message)\n");

      return CURLE_BAD_CONTENT_ENCODING;
    }

    /* Setup the challenge "input" security buffer */
    input_token.value = chlg;
    input_token.length = chlglen;
  }

  gss_major_status = Curl_gss_init_sec_context(data,
                                               &gss_minor_status,
                                               &krb5->context,
                                               krb5->spn,
                                               &Curl_krb5_mech_oid,
                                               GSS_C_NO_CHANNEL_BINDINGS,
                                               &input_token,
                                               &output_token,
                                               mutual_auth,
                                               NULL);

  Curl_safefree(input_token.value);

  if(GSS_ERROR(gss_major_status)) {
    if(output_token.value)
      gss_release_buffer(&gss_status, &output_token);

    Curl_gss_log_error(data, gss_minor_status,
                       "gss_init_sec_context() failed: ");

    return CURLE_RECV_ERROR;
  }

  if(output_token.value && output_token.length) {
    /* Base64 encode the response */
    result = Curl_base64_encode(data, (char *) output_token.value,
                                output_token.length, outptr, outlen);

    gss_release_buffer(&gss_status, &output_token);
  }

  return result;
}