static CURLcode servercert(struct connectdata *conn,
                           struct ssl_connect_data *connssl,
                           bool strict)
{
  CURLcode retcode = CURLE_OK;
  char *str;
  long lerr;
  ASN1_TIME *certdate;
  struct SessionHandle *data = conn->data;
  connssl->server_cert = SSL_get_peer_certificate(connssl->handle);
  if(!connssl->server_cert) {
    if(strict)
      failf(data, "SSL: couldn't get peer certificate!");
    return CURLE_PEER_FAILED_VERIFICATION;
  }
  infof (data, "Server certificate:\n");

  str = X509_NAME_oneline(X509_get_subject_name(connssl->server_cert),
                          NULL, 0);
  if(!str) {
    if(strict)
      failf(data, "SSL: couldn't get X509-subject!");
    X509_free(connssl->server_cert);
    connssl->server_cert = NULL;
    return CURLE_SSL_CONNECT_ERROR;
  }
  infof(data, "\t subject: %s\n", str);
  CRYPTO_free(str);

  certdate = X509_get_notBefore(connssl->server_cert);
  asn1_output(conn, "\t start date: ", certdate);

  certdate = X509_get_notAfter(connssl->server_cert);
  asn1_output(conn, "\t expire date: ", certdate);

  if(data->set.ssl.verifyhost) {
    retcode = verifyhost(conn, connssl->server_cert);
    if(retcode) {
      X509_free(connssl->server_cert);
      connssl->server_cert = NULL;
      return retcode;
    }
  }

  str = X509_NAME_oneline(X509_get_issuer_name(connssl->server_cert),
                          NULL, 0);
  if(!str) {
    if(strict)
      failf(data, "SSL: couldn't get X509-issuer name!");
    retcode = CURLE_SSL_CONNECT_ERROR;
  }
  else {
    infof(data, "\t issuer: %s\n", str);
    CRYPTO_free(str);

    /* We could do all sorts of certificate verification stuff here before
       deallocating the certificate. */

    lerr = data->set.ssl.certverifyresult=
      SSL_get_verify_result(connssl->handle);
    if(data->set.ssl.certverifyresult != X509_V_OK) {
      if(data->set.ssl.verifypeer) {
        /* We probably never reach this, because SSL_connect() will fail
           and we return earlyer if verifypeer is set? */
        if(strict)
          failf(data, "SSL certificate verify result: %s (%ld)",
                X509_verify_cert_error_string(lerr), lerr);
        retcode = CURLE_PEER_FAILED_VERIFICATION;
      }
      else
        infof(data, "SSL certificate verify result: %s (%ld),"
              " continuing anyway.\n",
              X509_verify_cert_error_string(lerr), lerr);
    }
    else
      infof(data, "SSL certificate verify ok.\n");
  }

  X509_free(connssl->server_cert);
  connssl->server_cert = NULL;
  connssl->connecting_state = ssl_connect_done;

  return retcode;
}