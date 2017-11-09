static void Curl_mbedtls_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  mbedtls_pk_free(&BACKEND->pk);
  mbedtls_x509_crt_free(&BACKEND->clicert);
  mbedtls_x509_crt_free(&BACKEND->cacert);
  mbedtls_x509_crl_free(&BACKEND->crl);
  mbedtls_ssl_config_free(&BACKEND->config);
  mbedtls_ssl_free(&BACKEND->ssl);
  mbedtls_ctr_drbg_free(&BACKEND->ctr_drbg);
#ifndef THREADING_SUPPORT
  mbedtls_entropy_free(&BACKEND->entropy);
#endif /* THREADING_SUPPORT */
}