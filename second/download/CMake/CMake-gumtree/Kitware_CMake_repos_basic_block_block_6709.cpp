{
    gnutls_certificate_free_credentials(ssl->cred);
    ssl->cred = NULL;
  }