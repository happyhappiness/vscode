static void close_one(struct ssl_connect_data *ssl)
{
  if(ssl->session) {
    gnutls_bye(ssl->session, GNUTLS_SHUT_RDWR);
    gnutls_deinit(ssl->session);
    ssl->session = NULL;
  }
  if(ssl->cred) {
    gnutls_certificate_free_credentials(ssl->cred);
    ssl->cred = NULL;
  }
#ifdef USE_TLS_SRP
  if(ssl->srp_client_cred) {
    gnutls_srp_free_client_credentials(ssl->srp_client_cred);
    ssl->srp_client_cred = NULL;
  }
#endif
}