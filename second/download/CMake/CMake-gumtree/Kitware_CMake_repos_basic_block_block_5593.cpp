{
        failf(data, "Failed to send SSPI authentication request.");
        free(service_name);
        if(sspi_send_token.pvBuffer)
          s_pSecFn->FreeContextBuffer(sspi_send_token.pvBuffer);
        if(sspi_recv_token.pvBuffer)
          s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
        s_pSecFn->FreeCredentialsHandle(&cred_handle);
        s_pSecFn->DeleteSecurityContext(&sspi_context);
        return CURLE_COULDNT_CONNECT;
      }