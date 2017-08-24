{
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      failf(data, "Failed to query security context attributes.");
      return CURLE_COULDNT_CONNECT;
    }