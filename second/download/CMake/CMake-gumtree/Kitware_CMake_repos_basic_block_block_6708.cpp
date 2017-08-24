{
    gnutls_srp_free_client_credentials(ssl->srp_client_cred);
    ssl->srp_client_cred = NULL;
  }