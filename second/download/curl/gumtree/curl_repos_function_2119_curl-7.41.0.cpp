static CURLcode servercert(struct connectdata *conn,
                           struct ssl_connect_data *connssl,
                           bool strict)
{
  CURLcode result = CURLE_OK;
  int rc;
  long lerr;
  ASN1_TIME *certdate;
  struct SessionHandle *data = conn->data;
  X509 *issuer;
  FILE *fp;
  char *buffer = data->state.buffer;
  const char *ptr;

  if(data->set.ssl.certinfo)
    /* we've been asked to gather certificate info! */
    (void)get_cert_chain(conn, connssl);

  connssl->server_cert = SSL_get_peer_certificate(connssl->handle);
  if(!connssl->server_cert) {
    if(strict)
      failf(data, "SSL: couldn't get peer certificate!");
    return CURLE_PEER_FAILED_VERIFICATION;
  }

  infof(data, "Server certificate:\n");

  rc = x509_name_oneline(X509_get_subject_name(connssl->server_cert),
                         buffer, BUFSIZE);
  infof(data, "\t subject: %s\n", rc?"[NONE]":buffer);

  certdate = X509_get_notBefore(connssl->server_cert);
  asn1_output(certdate, buffer, BUFSIZE);
  infof(data, "\t start date: %s\n", buffer);

  certdate = X509_get_notAfter(connssl->server_cert);
  asn1_output(certdate, buffer, BUFSIZE);
  infof(data, "\t expire date: %s\n", buffer);

  if(data->set.ssl.verifyhost) {
    result = verifyhost(conn, connssl->server_cert);
    if(result) {
      X509_free(connssl->server_cert);
      connssl->server_cert = NULL;
      return result;
    }
  }

  rc = x509_name_oneline(X509_get_issuer_name(connssl->server_cert),
                         buffer, BUFSIZE);
  if(rc) {
    if(strict)
      failf(data, "SSL: couldn't get X509-issuer name!");
    result = CURLE_SSL_CONNECT_ERROR;
  }
  else {
    infof(data, "\t issuer: %s\n", buffer);

    /* We could do all sorts of certificate verification stuff here before
       deallocating the certificate. */

    /* e.g. match issuer name with provided issuer certificate */
    if(data->set.str[STRING_SSL_ISSUERCERT]) {
      fp = fopen(data->set.str[STRING_SSL_ISSUERCERT], "r");
      if(!fp) {
        if(strict)
          failf(data, "SSL: Unable to open issuer cert (%s)",
                data->set.str[STRING_SSL_ISSUERCERT]);
        X509_free(connssl->server_cert);
        connssl->server_cert = NULL;
        return CURLE_SSL_ISSUER_ERROR;
      }

      issuer = PEM_read_X509(fp, NULL, ZERO_NULL, NULL);
      if(!issuer) {
        if(strict)
          failf(data, "SSL: Unable to read issuer cert (%s)",
                data->set.str[STRING_SSL_ISSUERCERT]);
        X509_free(connssl->server_cert);
        X509_free(issuer);
        fclose(fp);
        return CURLE_SSL_ISSUER_ERROR;
      }

      fclose(fp);

      if(X509_check_issued(issuer,connssl->server_cert) != X509_V_OK) {
        if(strict)
          failf(data, "SSL: Certificate issuer check failed (%s)",
                data->set.str[STRING_SSL_ISSUERCERT]);
        X509_free(connssl->server_cert);
        X509_free(issuer);
        connssl->server_cert = NULL;
        return CURLE_SSL_ISSUER_ERROR;
      }

      infof(data, "\t SSL certificate issuer check ok (%s)\n",
            data->set.str[STRING_SSL_ISSUERCERT]);
      X509_free(issuer);
    }

    lerr = data->set.ssl.certverifyresult =
      SSL_get_verify_result(connssl->handle);

    if(data->set.ssl.certverifyresult != X509_V_OK) {
      if(data->set.ssl.verifypeer) {
        /* We probably never reach this, because SSL_connect() will fail
           and we return earlier if verifypeer is set? */
        if(strict)
          failf(data, "SSL certificate verify result: %s (%ld)",
                X509_verify_cert_error_string(lerr), lerr);
        result = CURLE_PEER_FAILED_VERIFICATION;
      }
      else
        infof(data, "\t SSL certificate verify result: %s (%ld),"
              " continuing anyway.\n",
              X509_verify_cert_error_string(lerr), lerr);
    }
    else
      infof(data, "\t SSL certificate verify ok.\n");
  }

#if (OPENSSL_VERSION_NUMBER >= 0x0090808fL) && !defined(OPENSSL_NO_TLSEXT) && \
    !defined(OPENSSL_IS_BORINGSSL)
  if(data->set.ssl.verifystatus) {
    result = verifystatus(conn, connssl);
    if(result) {
      X509_free(connssl->server_cert);
      connssl->server_cert = NULL;
      return result;
    }
  }
#endif

  if(!strict)
    /* when not strict, we don't bother about the verify cert problems */
    result = CURLE_OK;

  ptr = data->set.str[STRING_SSL_PINNEDPUBLICKEY];
  if(!result && ptr) {
    result = pkp_pin_peer_pubkey(connssl->server_cert, ptr);
    if(result)
      failf(data, "SSL: public key does not match pinned public key!");
  }

  X509_free(connssl->server_cert);
  connssl->server_cert = NULL;
  connssl->connecting_state = ssl_connect_done;

  return result;
}