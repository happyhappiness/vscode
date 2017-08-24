f(SSL_SET_OPTION(CRLfile)) {
    /* set the CRL list file */
    rc = gnutls_certificate_set_x509_crl_file(conn->ssl[sockindex].cred,
                                              SSL_SET_OPTION(CRLfile),
                                              GNUTLS_X509_FMT_PEM);
    if(rc < 0) {
      failf(data, "error reading crl file %s (%s)",
            SSL_SET_OPTION(CRLfile), gnutls_strerror(rc));
      return CURLE_SSL_CRL_BADFILE;
    }
    else
      infof(data, "found %d CRL in %s\n",
            rc, SSL_SET_OPTION(CRLfile));
  }