{
  CURLcode result = CURLE_OK;
  TCHAR *spn = NULL;
  size_t chlglen = 0;
  size_t token_max = 0;
  unsigned char *input_token = NULL;
  unsigned char *output_token = NULL;
  CredHandle credentials;
  CtxtHandle context;
  PSecPkgInfo SecurityPackage;
  SEC_WINNT_AUTH_IDENTITY identity;
  SEC_WINNT_AUTH_IDENTITY *p_identity;
  SecBuffer chlg_buf;
  SecBuffer resp_buf;
  SecBufferDesc chlg_desc;
  SecBufferDesc resp_desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */

  /* Decode the base-64 encoded challenge message */
  if(strlen(chlg64) && *chlg64 != '=') {
    result = Curl_base64_decode(chlg64, &input_token, &chlglen);
    if(result)
      return result;
  }

  /* Ensure we have a valid challenge message */
  if(!input_token) {
    infof(data, "DIGEST-MD5 handshake failure (empty challenge message)\n");

    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Query the security package for DigestSSP */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT(SP_NAME_DIGEST),
                                              &SecurityPackage);
  if(status != SEC_E_OK) {
    free(input_token);

    return CURLE_NOT_BUILT_IN;
  }

  token_max = SecurityPackage->cbMaxToken;

  /* Release the package buffer as it is not required anymore */
  s_pSecFn->FreeContextBuffer(SecurityPackage);

  /* Allocate our response buffer */
  output_token = malloc(token_max);
  if(!output_token) {
    free(input_token);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Generate our SPN */
  spn = Curl_auth_build_spn(service, data->easy_conn->host.name, NULL);
  if(!spn) {
    free(output_token);
    free(input_token);

    return CURLE_OUT_OF_MEMORY;
  }

  if(userp && *userp) {
    /* Populate our identity structure */
    result = Curl_create_sspi_identity(userp, passwdp, &identity);
    if(result) {
      free(spn);
      free(output_token);
      free(input_token);

      return result;
    }

    /* Allow proper cleanup of the identity structure */
    p_identity = &identity;
  }
  else
    /* Use the current Windows user */
    p_identity = NULL;

  /* Acquire our credentials handle */
  status = s_pSecFn->AcquireCredentialsHandle(NULL,
                                              (TCHAR *) TEXT(SP_NAME_DIGEST),
                                              SECPKG_CRED_OUTBOUND, NULL,
                                              p_identity, NULL, NULL,
                                              &credentials, &expiry);

  if(status != SEC_E_OK) {
    Curl_sspi_free_identity(p_identity);
    free(spn);
    free(output_token);
    free(input_token);

    return CURLE_LOGIN_DENIED;
  }

  /* Setup the challenge "input" security buffer */
  chlg_desc.ulVersion = SECBUFFER_VERSION;
  chlg_desc.cBuffers  = 1;
  chlg_desc.pBuffers  = &chlg_buf;
  chlg_buf.BufferType = SECBUFFER_TOKEN;
  chlg_buf.pvBuffer   = input_token;
  chlg_buf.cbBuffer   = curlx_uztoul(chlglen);

  /* Setup the response "output" security buffer */
  resp_desc.ulVersion = SECBUFFER_VERSION;
  resp_desc.cBuffers  = 1;
  resp_desc.pBuffers  = &resp_buf;
  resp_buf.BufferType = SECBUFFER_TOKEN;
  resp_buf.pvBuffer   = output_token;
  resp_buf.cbBuffer   = curlx_uztoul(token_max);

  /* Generate our response message */
  status = s_pSecFn->InitializeSecurityContext(&credentials, NULL, spn,
                                               0, 0, 0, &chlg_desc, 0,
                                               &context, &resp_desc, &attrs,
                                               &expiry);

  if(status == SEC_I_COMPLETE_NEEDED ||
     status == SEC_I_COMPLETE_AND_CONTINUE)
    s_pSecFn->CompleteAuthToken(&credentials, &resp_desc);
  else if(status != SEC_E_OK && status != SEC_I_CONTINUE_NEEDED) {
    s_pSecFn->FreeCredentialsHandle(&credentials);
    Curl_sspi_free_identity(p_identity);
    free(spn);
    free(output_token);
    free(input_token);

    return CURLE_RECV_ERROR;
  }

  /* Base64 encode the response */
  result = Curl_base64_encode(data, (char *) output_token, resp_buf.cbBuffer,
                              outptr, outlen);

  /* Free our handles */
  s_pSecFn->DeleteSecurityContext(&context);
  s_pSecFn->FreeCredentialsHandle(&credentials);

  /* Free the identity structure */
  Curl_sspi_free_identity(p_identity);

  /* Free the SPN */
  free(spn);

  /* Free the response buffer */
  free(output_token);

  /* Free the decoded challenge message */
  free(input_token);

  return result;
}