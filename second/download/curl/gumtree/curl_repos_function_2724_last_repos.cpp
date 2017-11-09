static void close_one(struct ssl_connect_data *connssl)
{
  if(BACKEND->session) {
    gnutls_bye(BACKEND->session, GNUTLS_SHUT_RDWR);
    gnutls_deinit(BACKEND->session);
    BACKEND->session = NULL;
  }
  if(BACKEND->cred) {
    gnutls_certificate_free_credentials(BACKEND->cred);
    BACKEND->cred = NULL;
  }
#ifdef USE_TLS_SRP
  if(BACKEND->srp_client_cred) {
    gnutls_srp_free_client_credentials(BACKEND->srp_client_cred);
    BACKEND->srp_client_cred = NULL;
  }
#endif
}