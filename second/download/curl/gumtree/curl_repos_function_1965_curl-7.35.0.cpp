static CURLcode Curl_qsossl_handshake(struct connectdata * conn, int sockindex)

{
  int rc;
  struct SessionHandle * data = conn->data;
  struct ssl_connect_data * connssl = &conn->ssl[sockindex];
  SSLHandle * h = connssl->handle;
  long timeout_ms;

  h->exitPgm = data->set.ssl.verifypeer? NULL: Curl_qsossl_trap_cert;

  /* figure out how long time we should wait at maximum */
  timeout_ms = Curl_timeleft(data, NULL, TRUE);

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
    h->protocol = SSL_VERSION_CURRENT;          /* TLSV1 compat. SSLV[23]. */
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

  case CURL_SSLVERSION_TLSv1_0:
  case CURL_SSLVERSION_TLSv1_1:
  case CURL_SSLVERSION_TLSv1_2:
    failf(data, "TLS minor version cannot be set");
    return CURLE_SSL_CONNECT_ERROR;
  }

  h->peerCert = NULL;
  h->peerCertLen = 0;
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
    failf(data, "SSL_Handshake() I/O error: %s", strerror(errno));
    return CURLE_SSL_CONNECT_ERROR;

  default:
    failf(data, "SSL_Handshake(): %s", SSL_Strerror(rc, NULL));
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* Verify host. */
  rc = Curl_verifyhost(conn, h->peerCert, h->peerCert + h->peerCertLen);
  if(rc != CURLE_OK)
    return rc;

  /* Gather certificate info. */
  if(data->set.ssl.certinfo) {
    if(Curl_ssl_init_certinfo(data, 1))
      return CURLE_OUT_OF_MEMORY;
    if(h->peerCert) {
      rc = Curl_extract_certinfo(conn, 0, h->peerCert,
                                 h->peerCert + h->peerCertLen);
      if(rc != CURLE_OK)
        return rc;
    }
  }

  return CURLE_OK;
}