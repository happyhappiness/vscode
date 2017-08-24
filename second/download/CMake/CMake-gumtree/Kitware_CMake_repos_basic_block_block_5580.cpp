{
      failf(data, "Failed to receive SSPI authentication token.");
      free(service_name);
      if(sspi_recv_token.pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }