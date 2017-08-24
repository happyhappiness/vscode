{
  CURLcode result = CURLE_OK;
  size_t chlglen = 0;
  unsigned char *chlg = NULL;
  CtxtHandle context;
  PSecPkgInfo SecurityPackage;
  SecBuffer chlg_buf;
  SecBuffer resp_buf;
  SecBufferDesc chlg_desc;
  SecBufferDesc resp_desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */

  if(!krb5->spn) {
    /* Generate our SPN */
    krb5->spn = Curl_auth_build_spn(service, host, NULL);
    if(!krb5->spn)
      return CURLE_OUT_OF_MEMORY;
  }

  if(!krb5->output_token) {
    /* Query the security package for Kerberos */
    status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *)
                                                TEXT(SP_NAME_KERBEROS),
                                                &SecurityPackage);
    if(status != SEC_E_OK) {
      return CURLE_NOT_BUILT_IN;
    }

    krb5->token_max = SecurityPackage->cbMaxToken;

    /* Release the package buffer as it is not required anymore */
    s_pSecFn->FreeContextBuffer(SecurityPackage);

    /* Allocate our response buffer */
    krb5->output_token = malloc(krb5->token_max);
    if(!krb5->output_token)
      return CURLE_OUT_OF_MEMORY;
  }

  if(!krb5->credentials) {
    /* Do we have credientials to use or are we using single sign-on? */
    if(userp && *userp) {
      /* Populate our identity structure */
      result = Curl_create_sspi_identity(userp, passwdp, &krb5->identity);
      if(result)
        return result;

      /* Allow proper cleanup of the identity structure */
      krb5->p_identity = &krb5->identity;
    }
    else
      /* Use the current Windows user */
      krb5->p_identity = NULL;

    /* Allocate our credentials handle */
    krb5->credentials = malloc(sizeof(CredHandle));
    if(!krb5->credentials)
      return CURLE_OUT_OF_MEMORY;

    memset(krb5->credentials, 0, sizeof(CredHandle));

    /* Acquire our credentials handle */
    status = s_pSecFn->AcquireCredentialsHandle(NULL,
                                                (TCHAR *)
                                                TEXT(SP_NAME_KERBEROS),
                                                SECPKG_CRED_OUTBOUND, NULL,
                                                krb5->p_identity, NULL, NULL,
                                                krb5->credentials, &expiry);
    if(status != SEC_E_OK)
      return CURLE_LOGIN_DENIED;

    /* Allocate our new context handle */
    krb5->context = malloc(sizeof(CtxtHandle));
    if(!krb5->context)
      return CURLE_OUT_OF_MEMORY;

    memset(krb5->context, 0, sizeof(CtxtHandle));
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
      infof(data, "GSSAPI handshake failure (empty challenge message)\n");

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
  resp_buf.pvBuffer   = krb5->output_token;
  resp_buf.cbBuffer   = curlx_uztoul(krb5->token_max);

  /* Generate our challenge-response message */
  status = s_pSecFn->InitializeSecurityContext(krb5->credentials,
                                               chlg ? krb5->context : NULL,
                                               krb5->spn,
                                               (mutual_auth ?
                                                ISC_REQ_MUTUAL_AUTH : 0),
                                               0, SECURITY_NATIVE_DREP,
                                               chlg ? &chlg_desc : NULL, 0,
                                               &context,
                                               &resp_desc, &attrs,
                                               &expiry);

  /* Free the decoded challenge as it is not required anymore */
  free(chlg);

  if(status != SEC_E_OK && status != SEC_I_CONTINUE_NEEDED) {
    return CURLE_RECV_ERROR;
  }

  if(memcmp(&context, krb5->context, sizeof(context))) {
    s_pSecFn->DeleteSecurityContext(krb5->context);

    memcpy(krb5->context, &context, sizeof(context));
  }

  if(resp_buf.cbBuffer) {
    /* Base64 encode the response */
    result = Curl_base64_encode(data, (char *) resp_buf.pvBuffer,
                                resp_buf.cbBuffer, outptr, outlen);
  }
  else if(mutual_auth) {
    *outptr = strdup("");
    if(!*outptr)
      result = CURLE_OUT_OF_MEMORY;
  }

  return result;
}