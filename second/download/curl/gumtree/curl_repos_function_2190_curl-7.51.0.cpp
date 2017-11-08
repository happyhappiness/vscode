CURLcode Curl_auth_create_gssapi_security_message(struct Curl_easy *data,
                                                  const char *chlg64,
                                                  struct kerberos5data *krb5,
                                                  char **outptr,
                                                  size_t *outlen)
{
  CURLcode result = CURLE_OK;
  size_t offset = 0;
  size_t chlglen = 0;
  size_t messagelen = 0;
  size_t appdatalen = 0;
  unsigned char *chlg = NULL;
  unsigned char *trailer = NULL;
  unsigned char *message = NULL;
  unsigned char *padding = NULL;
  unsigned char *appdata = NULL;
  SecBuffer input_buf[2];
  SecBuffer wrap_buf[3];
  SecBufferDesc input_desc;
  SecBufferDesc wrap_desc;
  unsigned long indata = 0;
  unsigned long outdata = 0;
  unsigned long qop = 0;
  unsigned long sec_layer = 0;
  unsigned long max_size = 0;
  SecPkgContext_Sizes sizes;
  SecPkgCredentials_Names names;
  SECURITY_STATUS status;
  char *user_name;

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

  /* Get our response size information */
  status = s_pSecFn->QueryContextAttributes(krb5->context,
                                            SECPKG_ATTR_SIZES,
                                            &sizes);
  if(status != SEC_E_OK) {
    free(chlg);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Get the fully qualified username back from the context */
  status = s_pSecFn->QueryCredentialsAttributes(krb5->credentials,
                                                SECPKG_CRED_ATTR_NAMES,
                                                &names);
  if(status != SEC_E_OK) {
    free(chlg);

    return CURLE_RECV_ERROR;
  }

  /* Setup the "input" security buffer */
  input_desc.ulVersion = SECBUFFER_VERSION;
  input_desc.cBuffers = 2;
  input_desc.pBuffers = input_buf;
  input_buf[0].BufferType = SECBUFFER_STREAM;
  input_buf[0].pvBuffer = chlg;
  input_buf[0].cbBuffer = curlx_uztoul(chlglen);
  input_buf[1].BufferType = SECBUFFER_DATA;
  input_buf[1].pvBuffer = NULL;
  input_buf[1].cbBuffer = 0;

  /* Decrypt the inbound challenge and obtain the qop */
  status = s_pSecFn->DecryptMessage(krb5->context, &input_desc, 0, &qop);
  if(status != SEC_E_OK) {
    infof(data, "GSSAPI handshake failure (empty security message)\n");

    free(chlg);

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Not 4 octets long so fail as per RFC4752 Section 3.1 */
  if(input_buf[1].cbBuffer != 4) {
    infof(data, "GSSAPI handshake failure (invalid security data)\n");

    free(chlg);

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Copy the data out and free the challenge as it is not required anymore */
  memcpy(&indata, input_buf[1].pvBuffer, 4);
  s_pSecFn->FreeContextBuffer(input_buf[1].pvBuffer);
  free(chlg);

  /* Extract the security layer */
  sec_layer = indata & 0x000000FF;
  if(!(sec_layer & KERB_WRAP_NO_ENCRYPT)) {
    infof(data, "GSSAPI handshake failure (invalid security layer)\n");

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

  /* Allocate the trailer */
  trailer = malloc(sizes.cbSecurityTrailer);
  if(!trailer)
    return CURLE_OUT_OF_MEMORY;

  /* Convert the user name to UTF8 when operating with Unicode */
  user_name = Curl_convert_tchar_to_UTF8(names.sUserName);
  if(!user_name) {
    free(trailer);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Allocate our message */
  messagelen = sizeof(outdata) + strlen(user_name) + 1;
  message = mall