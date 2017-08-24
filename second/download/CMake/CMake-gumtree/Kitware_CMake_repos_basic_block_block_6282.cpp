{
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