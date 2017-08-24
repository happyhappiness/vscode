{
    gnutls_bye(ssl->session, GNUTLS_SHUT_RDWR);
    gnutls_deinit(ssl->session);
    ssl->session = NULL;
  }