static CURLcode Curl_qsossl_handshake(struct connectdata * conn, int sockindex)

{
  int rc;
  struct SessionHandle * data = conn->data;
  struct ssl_connect_data * connssl = &conn->ssl[sockindex];
  SSLHandle * h = connssl->handle;
  long timeout_ms;

  h->exitPgm = NULL;

  if(!data->set.ssl.verifyhost)
    h->exitPgm = Curl_qsossl_trap_cert;

  /* figure out how long time we should wait at maximum */
  timeout_ms = Curl_timeleft(conn, NULL, TRUE);

  if(timeout_ms < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  /* SSL_Handshake() timeout resolution is second, so round up. */
  h->timeout = (timeout_ms + 1000 - 1) / 1000;

  /* Set-up protocol. */

  switch (data->set.ssl.version) {

  default:
  case CURL_SSLVERSION_DEFAULT:
    h->protocol = TLSV1_SSLV3;
    break;

  case CURL_SSLVERSION_TLSv1:
    h->protocol = TLS_VERSION_1;
    break;

  case CURL_SSLVERSION_SSLv2:
    h->protocol = SSL_VERSION_2;
    break;

  case CURL_SSLVERSION_SSLv3:
    h->protocol = SSL_VERSION_3;
    break;
  }

  rc = SSL_Handshake(h, SSL_HANDSHAKE_AS_CLIENT);

  switch (rc) {

  case 0:                             /* No error. */
    break;

  case SSL_ERROR_BAD_CERTIFICATE:
  case SSL_ERROR_BAD_CERT_SIG:
  case SSL_ERROR_NOT_TRUSTED_ROOT:
    return CURLE_PEER_FAILED_VERIFICATION;

  case SSL_ERROR_BAD_CIPHER_SUITE:
  case SSL_ERROR_NO_CIPHERS:
    return CURLE_SSL_CIPHER;

  case SSL_ERROR_CERTIFICATE_REJECTED:
  case SSL_ERROR_CERT_EXPIRED:
  case SSL_ERROR_NO_CERTIFICATE:
    return CURLE_SSL_CERTPROBLEM;

  case SSL_ERROR_IO:
    failf(data, "SSL_Handshake(): %s", SSL_Strerror(rc, NULL));
    return CURLE_SSL_CONNECT_ERROR;

  default:
    failf(data, "SSL_Init(): %s", SSL_Strerror(rc, NULL));
    return CURLE_SSL_CONNECT_ERROR;
  }

  return CURLE_OK;
}