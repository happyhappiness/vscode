{
  PSecPkgInfo SecurityPackage;
  SecBuffer type_1_buf;
  SecBufferDesc type_1_desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */

  /* Clean up any former leftovers and initialise to defaults */
  Curl_auth_ntlm_cleanup(ntlm);

  /* Query the security package for NTLM */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT(SP_NAME_NTLM),
                                              &SecurityPackage);
  if(status != SEC_E_OK)
    return CURLE_NOT_BUILT_IN;

  ntlm->token_max = SecurityPackage->cbMaxToken;

  /* Release the package buffer as it is not required anymore */
  s_pSecFn->FreeContextBuffer(SecurityPackage);

  /* Allocate our output buffer */
  ntlm->output_token = malloc(ntlm->token_max);
  if(!ntlm->output_token)
    return CURLE_OUT_OF_MEMORY;

  if(userp && *userp) {
    CURLcode result;

    /* Populate our identity structure */
    result = Curl_create_sspi_identity(userp, passwdp, &ntlm->identity);
    if(result)
      return result;

    /* Allow proper cleanup of the identity structure */
    ntlm->p_identity = &ntlm->identity;
  }
  else
    /* Use the current Windows user */
    ntlm->p_identity = NULL;

  /* Allocate our credentials handle */
  ntlm->credentials = malloc(sizeof(CredHandle));
  if(!ntlm->credentials)
    return CURLE_OUT_OF_MEMORY;

  memset(ntlm->credentials, 0, sizeof(CredHandle));

  /* Acquire our credentials handle */
  status = s_pSecFn->AcquireCredentialsHandle(NULL,
                                              (TCHAR *) TEXT(SP_NAME_NTLM),
                                              SECPKG_CRED_OUTBOUND, NULL,
                                              ntlm->p_identity, NULL, NULL,
                                              ntlm->credentials, &expiry);
  if(status != SEC_E_OK)
    return CURLE_LOGIN_DENIED;

  /* Allocate our new context handle */
  ntlm->context = malloc(sizeof(CtxtHandle));
  if(!ntlm->context)
    return CURLE_OUT_OF_MEMORY;

  memset(ntlm->context, 0, sizeof(CtxtHandle));

  /* Setup the type-1 "output" security buffer */
  type_1_desc.ulVersion = SECBUFFER_VERSION;
  type_1_desc.cBuffers  = 1;
  type_1_desc.pBuffers  = &type_1_buf;
  type_1_buf.BufferType = SECBUFFER_TOKEN;
  type_1_buf.pvBuffer   = ntlm->output_token;
  type_1_buf.cbBuffer   = curlx_uztoul(ntlm->token_max);

  /* Generate our type-1 message */
  status = s_pSecFn->InitializeSecurityContext(ntlm->credentials, NULL,
                                               (TCHAR *) TEXT(""),
                                               0, 0, SECURITY_NETWORK_DREP,
                                               NULL, 0,
                                               ntlm->context, &type_1_desc,
                                               &attrs, &expiry);
  if(status == SEC_I_COMPLETE_NEEDED ||
    status == SEC_I_COMPLETE_AND_CONTINUE)
    s_pSecFn->CompleteAuthToken(ntlm->context, &type_1_desc);
  else if(status != SEC_E_OK && status != SEC_I_CONTINUE_NEEDED)
    return CURLE_RECV_ERROR;

  /* Base64 encode the response */
  return Curl_base64_encode(NULL, (char *) ntlm->output_token,
                            type_1_buf.cbBuffer, outptr, outlen);
}