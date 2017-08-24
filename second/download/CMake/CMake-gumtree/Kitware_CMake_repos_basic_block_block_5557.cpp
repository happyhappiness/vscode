f(!data->set.socks5_gssapi_nec) {
    wrap_desc.cBuffers = 2;
    sspi_w_token[0].BufferType = SECBUFFER_STREAM;
    sspi_w_token[1].BufferType = SECBUFFER_DATA;
    sspi_w_token[1].cbBuffer = 0;
    sspi_w_token[1].pvBuffer = NULL;

    status = s_pSecFn->DecryptMessage(&sspi_context,
                                      &wrap_desc,
                                      0,
                                      &qop);

    if(check_sspi_err(conn, status, "DecryptMessage")) {
      if(sspi_w_token[0].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
      if(sspi_w_token[1].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[1].pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      failf(data, "Failed to query security context attributes.");
      return CURLE_COULDNT_CONNECT;
    }

    if(sspi_w_token[1].cbBuffer != 1) {
      failf(data, "Invalid SSPI encryption response length (%lu).",
            (unsigned long)sspi_w_token[1].cbBuffer);
      if(sspi_w_token[0].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
      if(sspi_w_token[1].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[1].pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }

    memcpy(socksreq, sspi_w_token[1].pvBuffer, sspi_w_token[1].cbBuffer);
    s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
    s_pSecFn->FreeContextBuffer(sspi_w_token[1].pvBuffer);
  }
  else {
    if(sspi_w_token[0].cbBuffer != 1) {
      failf(data, "Invalid SSPI encryption response length (%lu).",
            (unsigned long)sspi_w_token[0].cbBuffer);
      s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }
    memcpy(socksreq, sspi_w_token[0].pvBuffer, sspi_w_token[0].cbBuffer);
    s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
  }