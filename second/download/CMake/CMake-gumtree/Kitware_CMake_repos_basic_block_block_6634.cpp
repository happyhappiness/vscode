f(SSL_CONN_CONFIG(CApath)) {
    /* set the trusted CA cert directory */
    rc = gnutls_certificate_set_x509_trust_dir(conn->ssl[sockindex].cred,
                                               SSL_CONN_CONFIG(CApath),
                                               GNUTLS_X509_FMT_PEM);
    if(rc < 0) {
      infof(data, "error reading ca cert file %s (%s)\n",
            SSL_CONN_CONFIG(CApath), gnutls_strerror(rc));
      if(SSL_CONN_CONFIG(verifypeer))
        return CURLE_SSL_CACERT_BADFILE;
    }
    else
      infof(data, "found %d certificates in %s\n",
            rc, SSL_CONN_CONFIG(CApath));
  }