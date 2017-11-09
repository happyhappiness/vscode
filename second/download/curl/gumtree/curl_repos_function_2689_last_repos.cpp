static void Curl_polarssl_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  rsa_free(&BACKEND->rsa);
  x509_crt_free(&BACKEND->clicert);
  x509_crt_free(&BACKEND->cacert);
  x509_crl_free(&BACKEND->crl);
  ssl_free(&BACKEND->ssl);
}