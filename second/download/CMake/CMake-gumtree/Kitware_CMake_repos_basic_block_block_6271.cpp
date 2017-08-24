{
  size_t token_max;
  char *resp;
  BYTE *output_token;
  size_t output_token_len = 0;
  PSecPkgInfo SecurityPackage;
  SecBuffer chlg_buf[5];
  SecBufferDesc chlg_desc;
  SECURITY_STATUS status;

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
  if(!output_token) {
    return CURLE_OUT_OF_MEMORY;
  }

  if(digest->http_context) {
    chlg_desc.ulVersion    = SECBUFFER_VERSION;
    chlg_desc.cBuffers     = 5;
    chlg_desc.pBuffers     = chlg_buf;
    chlg_buf[0].BufferType = SECBUFFER_TOKEN;
    chlg_buf[0].pvBuffer   = NULL;
    chlg_buf[0].cbBuffer   = 0;
    chlg_buf[1].BufferType = SECBUFFER_PKG_PARAMS;
    chlg_buf[1].pvBuffer   = (void *) request;
    chlg_buf[1].cbBuffer   = curlx_uztoul(strlen((const char *) request));
    chlg_buf[2].BufferType = SECBUFFER_PKG_PARAMS;
    chlg_buf[2].pvBuffer   = (void *) uripath;
    chlg_buf[2].cbBuffer   = curlx_uztoul(strlen((const char *) uripath));
    chlg_buf[3].BufferType = SECBUFFER_PKG_PARAMS;
    chlg_buf[3].pvBuffer   = NULL;
    chlg_buf[3].cbBuffer   = 0;
    chlg_buf[4].BufferType = SECBUFFER_PADDING;
    chlg_buf[4].pvBuffer   = output_token;
    chlg_buf[4].cbBuffer   = curlx_uztoul(token_max);

    status = s_pSecFn->MakeSignature(digest->http_context, 0, &chlg_desc, 0);
    if(status == SEC_E_OK)
      output_token_len = chlg_buf[4].cbBuffer;
    else { /* delete the context so a new one can be made */
      infof(data, "digest_sspi: MakeSignature failed, error 0x%08lx\n",
            (long)status);
      s_pSecFn->DeleteSecurityContext(digest->http_context);
      Curl_safefree(digest->http_context);
    }
  }

  if(!digest->http_context) {
    CredHandle credentials;
    SEC_WINNT_AUTH_IDENTITY identity;
    SEC_WINNT_AUTH_IDENTITY *p_identity;
    SecBuffer resp_buf;
    SecBufferDesc resp_desc;
    unsigned long attrs;
    TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */
    TCHAR *spn;

    if(userp && *userp) {
      /* Populate our identity structure */
      if(Curl_create_sspi_identity(userp, passwdp, &identity)) {
        free(output_token);
        return CURLE_OUT_OF_MEMORY;
      }

      /* Populate our identity domain */
      if(Curl_override_sspi_http_realm((const char *) digest->input_token,
                                       &identity)) {
        free(output_token);
        return CURLE_OUT_OF_MEMORY;
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
      free(output_token);

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
    chlg_buf[1].pvBuffer   = (void *) request;
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

    spn = Curl_convert_UTF8_to_tchar((char *) uripath);
    if(!spn) {
      s_pSecFn->FreeCredentialsHandle(&credentials);

      Curl_sspi_free_identity(p_identity);
      free(output_token);

      return CURLE_OUT_OF_MEMORY;
    }

    /* Allocate our new context handle */
    digest->http_context = calloc(1, sizeof(CtxtHandle));
    if(!digest->http_context)
      return CURLE_OUT_OF_MEMORY;

    /* Generate our response message */
    status = s_pSecFn->InitializeSecurityContext(&credentials, NULL,
                                                 spn,
                                                 ISC_REQ_USE_HTTP_STYLE, 0, 0,
                                                 &chlg_desc, 0,
                                                 digest->http_context,
                                                 &resp_desc, &attrs, &expiry);
    Curl_unicodefree(spn);

    if(status == SEC_I_COMPLETE_NEEDED ||
       status == SEC_I_COMPLETE_AND_CONTINUE)
      s_pSecFn->CompleteAuthToken(&credentials, &resp_desc);
    else if(status != SEC_E_OK && status != SEC_I_CONTINUE_NEEDED) {
      s_pSecFn->FreeCredentialsHandle(&credentials);

      Curl_sspi_free_identity(p_identity);
      free(output_token);

      Curl_safefree(digest->http_context);

      return CURLE_OUT_OF_MEMORY;
    }

    output_token_len = resp_buf.cbBuffer;

    s_pSecFn->FreeCredentialsHandle(&credentials);
    Curl_sspi_free_identity(p_identity);
  }

  resp = malloc(output_token_len + 1);
  if(!resp) {
    free(output_token);

    return CURLE_OUT_OF_MEMORY;
  }

  /* Copy the generated response */
  memcpy(resp, output_token, output_token_len);
  resp[output_token_len] = 0;

  /* Return the response */
  *outptr = resp;
  *outlen = output_token_len;

  /* Free the response buffer */
  free(output_token);

  return CURLE_OK;
}