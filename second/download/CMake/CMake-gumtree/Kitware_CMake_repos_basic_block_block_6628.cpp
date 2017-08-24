{
      failf(data, "error reading crl file %s (%s)",
            SSL_SET_OPTION(CRLfile), gnutls_strerror(rc));
      return CURLE_SSL_CRL_BADFILE;
    }