{
    failf(data, "Failed to acquire credentials.");
    free(service_name);
    s_pSecFn->FreeCredentialsHandle(&cred_handle);
    return CURLE_COULDNT_CONNECT;
  }