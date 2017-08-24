{
      failf(data, "Failed to send SSPI encryption type.");
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }