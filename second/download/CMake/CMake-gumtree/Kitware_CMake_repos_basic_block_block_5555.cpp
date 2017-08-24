f(sspi_w_token[1].cbBuffer != 1) {
      failf(data, "Invalid SSPI encryption response length (%lu).",
            (unsigned long)sspi_w_token[1].cbBuffer);
      if(sspi_w_token[0].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
      if(sspi_w_token[1].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[1].pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }