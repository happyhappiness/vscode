{
  CURLcode result = CURLE_OK;
  size_t chlglen = 0;
  size_t messagelen = 0;
  unsigned char *chlg = NULL;
  unsigned char *message = NULL;
  OM_uint32 major_status;
  OM_uint32 minor_status;
  OM_uint32 unused_status;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  unsigned int indata = 0;
  unsigned int outdata = 0;
  gss_qop_t qop = GSS_C_QOP_DEFAULT;
  unsigned int sec_layer = 0;
  unsigned int max_size = 0;
  gss_name_t username = GSS_C_NO_NAME;
  gss_buffer_desc username_token;

  /* Decode the base-64 encoded input message */
  if(strlen(chlg64) && *chlg64 != '=') {
    result = Curl_base64_decode(chlg64, &chlg, &chlglen);
    if(result)
      return result;
  }

  /* Ensure we have a valid challenge message */
  if(!chlg) {
    infof(data, "GSSAPI handshake failure (empty security message)\n");

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Get the fully qualified username back from the context */
  major_status = gss_inquire_context(&minor_status, krb5->context,
                                     &username, NULL, NULL, NULL, NULL,
                                     NULL, NULL);
  if(GSS_ERROR(major_status)) {
    Curl_gss_log_error(data, "gss_inquire_context() failed: ",
                       major_status, minor_status);

    free(chlg);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Convert the username from internal format to a displayable token */
  major_status = gss_display_name(&minor_status, username,
                                  &username_token, NULL);
  if(GSS_ERROR(major_status)) {
    Curl_gss_log_error(data, "gss_display_name() failed: ",
                       major_status, minor_status);

    free(chlg);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Setup the challenge "input" security buffer */
  input_token.value = chlg;
  input_token.length = chlglen;

  /* Decrypt the inbound challenge and obtain the qop */
  major_status = gss_unwrap(&minor_status, krb5->context, &input_token,
                            &output_token, NULL, &qop);
  if(GSS_ERROR(major_status)) {
    Curl_gss_log_error(data, "gss_unwrap() failed: ",
                       major_status, minor_status);

    gss_release_buffer(&unused_status, &username_token);
    free(chlg);

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Not 4 octets long so fail as per RFC4752 Section 3.1 */
  if(output_token.length != 4) {
    infof(data, "GSSAPI handshake failure (invalid security data)\n");

    gss_release_buffer(&unused_status, &username_token);
    free(chlg);

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Copy the data out and free the challenge as it is not required anymore */
  memcpy(&indata, output_token.value, 4);
  gss_release_buffer(&unused_status, &output_token);
  free(chlg);

  /* Extract the security layer */
  sec_layer = indata & 0x000000FF;
  if(!(sec_layer & GSSAUTH_P_NONE)) {
    infof(data, "GSSAPI handshake failure (invalid security layer)\n");

    gss_release_buffer(&unused_status, &username_token);

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Extract the maximum message size the server can receive */
  max_size = ntohl(indata & 0xFFFFFF00);
  if(max_size > 0) {
    /* The server has told us it supports a maximum receive buffer, however, as
       we don't require one unless we are encrypting data, we tell the server
       our receive buffer is zero. */
    max_size = 0;
  }

  /* Allocate our message */
  messagelen = sizeof(outdata) + username_token.length + 1;
  message = malloc(messagelen);
  if(!message) {
    gss_release_buffer(&unused_status, &username_token);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Populate the message with the security layer, client supported receive
     message size and authorization identity including the 0x00 based
     terminator. Note: Despite RFC4752 Section 3.1 stating "The authorization
     identity is not terminated with the zero-valued (%x00) octet." it seems
     necessary to include it. */
  outdata = htonl(max_size) | sec_layer;
  memcpy(message, &outdata, sizeof(outdata));
  memcpy(message + sizeof(outdata), username_token.value,
         username_token.length);
  message[messagelen - 1] = '\0';

  /* Free the username token as it is not required anymore */
  gss_release_buffer(&unused_status, &username_token);

  /* Setup the "authentication data" security buffer */
  input_token.value = message;
  input_token.length = messagelen;

  /* Encrypt the data */
  major_status = gss_wrap(&minor_status, krb5->context, 0,
                          GSS_C_QOP_DEFAULT, &input_token, NULL,
                          &output_token);
  if(GSS_ERROR(major_status)) {
    Curl_gss_log_error(data, "gss_wrap() failed: ",
                       major_status, minor_status);

    free(message);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Base64 encode the response */
  result = Curl_base64_encode(data, (char *) output_token.value,
                              output_token.length, outptr, outlen);

  /* Free the output buffer */
  gss_release_buffer(&unused_status, &output_token);

  /* Free the message buffer */
  free(message);

  return result;
}