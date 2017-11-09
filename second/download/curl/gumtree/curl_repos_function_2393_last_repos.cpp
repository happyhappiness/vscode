static CURLcode servercert(struct connectdata *conn,
                           struct ssl_connect_data *connssl,
                           bool strict)
{
  CURLcode result = CURLE_OK;
  int rc;
  long lerr, len;
  struct Curl_easy *data = conn->data;
  X509 *issuer;
  FILE *fp;
  char buffer[2048];
  const char *ptr;
  long * const certverifyresult = SSL_IS_PROXY() ?
    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
  BIO *mem = BIO_new(BIO_s_mem());

  if(data->set.ssl.certinfo)
    /* we've been asked to gather certificate info! */
    (void)get_cert_chain(conn, connssl);

  BACKEND->server_cert = SSL_get_peer_certificate(BACKEND->handle);
  if(!BACKEND->server_cert) {
    BIO_free(mem);
    if(!strict)
      return CURLE_OK;

    failf(data, "SSL: couldn't get peer certificate!");
    return CURLE_PEER_FAILED_VERIFICATION;
  }

  infof(data, "%s certificate:\n", SSL_IS_PROXY() ? "Proxy" : "Server");

  rc = x509_name_oneline(X509_get_subject_name(BACKEND->server_cert),
                         buffer, sizeof(buffer));
  infof(data, " subject: %s\n", rc?"[NONE]":buffer);

  ASN1_TIME_print(mem, X509_get0_notBefore(BACKEND->server_cert));
  len = BIO_get_mem_data(mem, (char **) &ptr);
  infof(data, " start date: %.*s\n", len, ptr);
  rc = BIO_reset(mem);

  ASN1_TIME_print(mem, X509_get0_notAfter(BACKEND->server_cert));
  len = BIO_get_mem_data(mem, (char **) &ptr);
  infof(data, " expire date: %.*s\n", len, ptr);
  rc = BIO_reset(mem);

  BIO_free(mem);

  if(SSL_CONN_CONFIG(verifyhost)) {
    result = verifyhost(conn, BACKEND->server_cert);
    if(result) {
      X509_free(BACKEND->server_cert);
      BACKEND->server_cert = NULL;
      return result;
    }
  }

  rc = x509_name_oneline(X509_get_issuer_name(BACKEND->server_cert),
                         buffer, sizeof(buffer));
  if(rc) {
    if(strict)
      failf(data, "SSL: couldn't get X509-issuer name!");
    result = CURLE_SSL_CONNECT_ERROR;
  }
  else {
    infof(data, " issuer: %s\n", buffer);

    /* We could do all sorts of certificate verification stuff here before
       deallocating the certificate. */

    /* e.g. match issuer name with provided issuer certificate */
    if(SSL_SET_OPTION(issuercert)) {
      fp = fopen(SSL_SET_OPTION(issuercert), FOPEN_READTEXT);
      if(!fp) {
        if(strict)
          failf(data, "SSL: Unable to open issuer cert (%s)",
                SSL_SET_OPTION(issuercert));
        X509_free(BACKEND->server_cert);
        BACKEND->server_cert = NULL;
        return CURLE_SSL_ISSUER_ERROR;
      }

      issuer = PEM_read_X509(fp, NULL, ZERO_NULL, NULL);
      if(!issuer) {
        if(strict)
          failf(data, "SSL: Unable to read issuer cert (%s)",
                SSL_SET_OPTION(issuercert));
        X509_free(BACKEND->server_cert);
        X509_free(issuer);
        fclose(fp);
        return CURLE_SSL_ISSUER_ERROR;
      }

      fclose(fp);

      if(X509_check_issued(issuer, BACKEND->server_cert) != X509_V_OK) {
        if(strict)
          failf(data, "SSL: Certificate issuer check failed (%s)",
                SSL_SET_OPTION(issuercert));
        X509_free(BACKEND->server_cert);
        X509_free(issuer);
        BACKEND->server_cert = NULL;
        return CURLE_SSL_ISSUER_ERROR;
      }

      infof(data, " SSL certificate issuer check ok (%s)\n",
            SSL_SET_OPTION(issuercert));
      X509_free(issuer);
    }

    lerr = *certverifyresult = SSL_get_verify_result(BACKEND->handle);

    if(*certverifyresult != X509_V_OK) {
      if(SSL_CONN_CONFIG(verifypeer)) {
        /* We probably never reach this, because SSL_connect() will fail
           and we return earlier if verifypeer is set? */
        if(strict)
          failf(data, "SSL certificate verify result: %s (%ld)",
                X509_verify_cert_error_string(lerr), lerr);
        result = CURLE_PEER_FAILED_VERIFICATION;
      }
      else
        infof(data, " SSL certificate verify result: %s (%ld),"
              " continuing anyway.\n",
              X509_verify_cert_error_string(lerr), lerr);
    }
    else
      infof(data, " SSL certificate verify ok.\n");
  }

#if (OPENSSL_VERSION_NUMBER >= 0x0090808fL) && !defined(OPENSSL_NO_TLSEXT) && \
    !defined(OPENSSL_NO_OCSP)
  if(SSL_CONN_CONFIG(verifystatus)) {
    result = verifystatus(conn, connssl);
    if(result) {
      X509_free(BACKEND->server_cert);
      BACKEND->server_cert = NULL;
      return result;
    }
  }
#endif

  if(!strict)
    /* when not strict, we don't bother about the verify cert problems */
    result = CURLE_OK;

  ptr = SSL_IS_PROXY() ? data->set.str[STRING_SSL_PINNEDPUBLICKEY_PROXY] :
                         data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG];
  if(!result && ptr) {
    result = pkp_pin_peer_pubkey(data, BACKEND->server_cert, ptr);
    if(result)
      failf(data, "SSL: public key does not match pinned public key!");
  }

  X509_free(BACKEND->server_cert);
  BACKEND->server_cert = NULL;
  connssl->connecting_state = ssl_connect_done;

  return result;
}