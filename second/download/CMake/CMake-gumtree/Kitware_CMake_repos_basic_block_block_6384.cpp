{
  CURLcode result = CURLE_OK;
  size_t chlglen = 0;
  unsigned char *chlg = NULL;
  PSecPkgInfo SecurityPackage;
  SecBuffer chlg_buf;
  SecBuffer resp_buf;
  SecBufferDesc chlg_desc;
  SecBufferDesc resp_desc;
  unsigned long attrs;
  TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) data;
#endif

  if(nego->context && nego->status == SEC_E_OK) {
    /* We finished successfully our part of authentication, but server
     * rejected it (since we're again here). Exit with an error since we
     * can't invent anything better */
    Curl_auth_spnego_cleanup(nego);
    return CURLE_LOGIN_DENIED;
  }

  if(!nego->spn) {
    /* Generate our SPN */
    nego->spn = Curl_auth_build_spn(service, host, NULL);
    if(!nego->spn)
      return CURLE_OUT_OF_MEMORY;
  }

  if(!nego->output_token) {
    /* Query the security package for Negotiate */
    nego->status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *)
                                                      TEXT(SP_NAME_NEGOTIATE),
                                                      &SecurityPackage);
    if(nego->status != SEC_E_OK)
      return CURLE_NOT_BUILT_IN;

    nego->token_max = SecurityPackage->cbMaxToken;

    /* Release the package buffer as it is not required anymore */
    s_pSecFn->FreeContextBuffer(SecurityPackage);

    /* Allocate our output buffer */
    nego->output_token = malloc(nego->token_max);
    if(!nego->output_token)
      return CURLE_OUT_OF_MEMORY;
 }

  if(!nego->credentials) {
    /* Do we have credientials to use or are we using single sign-on? */
    if(user && *user) {
      /* Populate our identity structure */
      result = Curl_create_sspi_identity(user, password, &nego->identity);
      if(result)
        return result;

      /* Allow proper cleanup of the identity structure */
      nego->p_identity = &nego->identity;
    }
    else
      /* Use the current Windows user */
      nego->p_identity = NULL;

    /* Allocate our credentials handle */
    nego->credentials = malloc(sizeof(CredHandle));
    if(!nego->credentials)
      return CURLE_OUT_OF_MEMORY;

    memset(nego->credentials, 0, sizeof(CredHandle));

    /* Acquire our credentials handle */
    nego->status =
      s_pSecFn->AcquireCredentialsHandle(NULL,
                                         (TCHAR *)TEXT(SP_NAME_NEGOTIATE),
                                         SECPKG_CRED_OUTBOUND, NULL,
                                         nego->p_identity, NULL, NULL,
                                         nego->credentials, &expiry);
    if(nego->status != SEC_E_OK)
      return CURLE_LOGIN_DENIED;

    /* Allocate our new context handle */
    nego->context = malloc(sizeof(CtxtHandle));
    if(!nego->context)
      return CURLE_OUT_OF_MEMORY;

    memset(nego->context, 0, sizeof(CtxtHandle));
  }

  if(chlg64 && *chlg64) {
    /* Decode the base-64 encoded challenge message */
    if(*chlg64 != '=') {
      result = Curl_base64_decode(chlg64, &chlg, &chlglen);
      if(result)
        return result;
    }

    /* Ensure we have a valid challenge message */
    if(!chlg) {
      infof(data, "SPNEGO handshake failure (empty challenge message)\n");

      return CURLE_BAD_CONTENT_ENCODING;
    }

    /* Setup the challenge "input" security buffer */
    chlg_desc.ulVersion = SECBUFFER_VERSION;
    chlg_desc.cBuffers  = 1;
    chlg_desc.pBuffers  = &chlg_buf;
    chlg_buf.BufferType = SECBUFFER_TOKEN;
    chlg_buf.pvBuffer   = chlg;
    chlg_buf.cbBuffer   = curlx_uztoul(chlglen);
  }

  /* Setup the response "output" security buffer */
  resp_desc.ulVersion = SECBUFFER_VERSION;
  resp_desc.cBuffers  = 1;
  resp_desc.pBuffers  = &resp_buf;
  resp_buf.BufferType = SECBUFFER_TOKEN;
  resp_buf.pvBuffer   = nego->output_token;
  resp_buf.cbBuffer   = curlx_uztoul(nego->token_max);

  /* Generate our challenge-response message */
  nego->status = s_pSecFn->InitializeSecurityContext(nego->credentials,
                                                     chlg ? nego->context :
                                                            NULL,
                                                     nego->spn,
                                                     ISC_REQ_CONFIDENTIALITY,
                                                     0, SECURITY_NATIVE_DREP,
                                                     chlg ? &chlg_desc : NULL,
                                                     0, nego->context,
                                                     &resp_desc, &attrs,
                                                     &expiry);

  /* Free the decoded challenge as it is not required anymore */
  free(chlg);

  if(GSS_ERROR(nego->status)) {
    failf(data, "InitializeSecurityContext failed: %s",
          Curl_sspi_strerror(data->easy_conn, nego->status));
    return CURLE_OUT_OF_MEMORY;
  }

  if(nego->status == SEC_I_COMPLETE_NEEDED ||
     nego->status == SEC_I_COMPLETE_AND_CONTINUE) {
    nego->status = s_pSecFn->CompleteAuthToken(nego->context, &resp_desc);
    if(GSS_ERROR(nego->status)) {
      return CURLE_RECV_ERROR;
    }
  }

  nego->output_token_length = resp_buf.cbBuffer;

  return result;
}