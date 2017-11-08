CURLcode Curl_sasl_create_digest_http_message(struct SessionHandle *data,
                                              const char *userp,
                                              const char *passwdp,
                                              const unsigned char *request,
                                              const unsigned char *uripath,
                                              struct digestdata *digest,
                                              char **outptr, size_t *outlen)
{
  size_t token_max;
  CredHandle credentials;
  CtxtHandle context;
  char *resp;
  BYTE *output_token;
  PSecPkgInfo SecurityPackage;
  SEC_WINNT_AUTH_IDENTITY identity;
  SEC_WINNT_AUTH_IDENTITY *p_identity;
  SecBuffer chlg_buf[3];
  SecBuffer resp_buf;
  SecBufferDesc chlg_desc;
  SecBufferDesc resp_desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */

  (void) data;

  /* Query the security package for DigestSSP */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT(SP_NAME_DIGEST),
                                              &SecurityPackage);
  if(status != SEC_E_OK)
    return CURLE_NOT_BUILT_IN;

  token_max = SecurityPackage->cbMaxToken;

  /* Release the package buffer as it is not required anymore */
  s_pSecFn->FreeContextBuffer(SecurityPackage);

  /* Allocate the output buffer according to the max token size as indicated
     by the security package */
  output_token = malloc(token_max);
  if(!output_token)
    return CURLE_OUT_OF_MEMORY;

  if(userp && *userp) {
    /* Populate our identity structure */
    if(Curl_create_sspi_identity(userp, passwdp, &identity))
      return CURLE_OUT_OF_MEMORY;

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
    Curl_safefree(output_token);

    return CURLE_LOGIN_DENIED;
  }

  /* Setup the challenge "input" security buffer if present */
  chlg_desc.ulVersion    = SECBUFFER_VERSION;
  chlg_desc.cBuffers     = 3;
  chlg_desc.pBuffers     = chlg_buf;
  chlg_buf[0].BufferType = SECBUFFER_TOKEN;
  chlg_buf[0].pvBuffer   = digest->input_token;
  chlg_buf[0].cbBuffer   = curlx_uztoul(digest->input_token_len);
  chlg_buf[1].BufferType = SECBUFFER_PKG_PARAMS;
  chlg_buf[1].pvBuffer   = (void *)request;
  chlg_buf[1].cbBuffer   = curlx_uztoul(strlen((const char *) request));
  chlg_buf[2].BufferType = SECBUFFER_PKG_PARAMS;
  chlg_buf[2].pvBuffer   = NULL;
  chlg_buf[2].cbBuffer   = 0;

  /* Setup the response "output" security buffer */
  resp_desc.ulVersion = SECBUFFER_VERSION;
  resp_desc.cBuffers  = 1;
  resp_desc.pBuffers  = &resp_buf;
  resp_buf.BufferType = SECBUFFER_TOKEN;
  resp_buf.pvBuffer   = output_token;
  resp_buf.cbBuffer   = curlx_uztoul(token_max);

  /* Generate our reponse message */
  status = s_pSecFn->InitializeSecurityContext(&credentials, NULL,
                                               (TCHAR *) uripath,
                                               ISC_REQ_USE_HTTP_STYLE, 0, 0,
                                               &chlg_desc, 0, &context,
                                               &resp_desc, &attrs, &expiry);

  if(status == SEC_I_COMPLETE_NEEDED ||
     status == SEC_I_COMPLETE_AND_CONTINUE)
    s_pSecFn->CompleteAuthToken(&credentials, &resp_desc);
  else if(status != SEC_E_OK && status != SEC_I_CONTINUE_NEEDED) {
    s_pSecFn->FreeCredentialsHandle(&credentials);

    Curl_safefree(output_token);

    return CURLE_OUT_OF_MEMORY;
  }

  resp = malloc(resp_buf.cbBuffer + 1);
  if(!resp) {
    s_pSecFn->DeleteSecurityContext(&context);
    s_pSecFn->FreeCredentialsHandle(&credentials);

    Curl_safefree(output_token);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Copy the generated reponse */
  memcpy(resp, resp_buf.pvBuffer, resp_buf.cbBuffer);
  resp[resp_buf.cbBuffer] = 0x00;

  /* Return the response */
  *outptr = resp;
  *outlen = resp_buf.cbBuffer;

  /* Free our handles */
  s_pSecFn->DeleteSecurityContext(&context);
  s_pSecFn->FreeCredentialsHandle(&credentials);

  /* Free the identity structure */
  Curl_sspi_free_identity(p_identity);

  /* Free the response buffer */
  Curl_safefree(output_token);

  return CURLE_OK;
}