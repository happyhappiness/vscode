{
      failf(data, "Failed to receive SSPI authentication response.");
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }