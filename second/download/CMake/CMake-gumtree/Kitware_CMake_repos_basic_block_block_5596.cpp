{
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      if(sspi_recv_token.pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      failf(data, "Failed to initialise security context.");
      return CURLE_COULDNT_CONNECT;
    }