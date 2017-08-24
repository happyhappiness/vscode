f(check_sspi_err(conn, status, "DecryptMessage")) {
      if(sspi_w_token[0].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
      if(sspi_w_token[1].pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_w_token[1].pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      failf(data, "Failed to query security context attributes.");
      return CURLE_COULDNT_CONNECT;
    }