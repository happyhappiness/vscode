f(rc != GNUTLS_E_SUCCESS) {
      failf(data, "gnutls_credentials_set() failed: %s", gnutls_strerror(rc));
      return CURLE_SSL_CONNECT_ERROR;
    }