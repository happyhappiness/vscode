{
      failf(data, "Failed to send SSPI encryption type.");
      if(sspi_send_token.pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_send_token.pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }