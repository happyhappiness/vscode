f(SSL_CONN_CONFIG(verifypeer)) {
      failf(data, "server cert expiration date verify failed");
      gnutls_x509_crt_deinit(x509_cert);
      return CURLE_SSL_CONNECT_ERROR;
    }
    else
      infof(data, "\t server certificate expiration date verify FAILED\n")