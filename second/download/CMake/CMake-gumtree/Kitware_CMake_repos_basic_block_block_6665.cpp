{
      failf(data, "server cert activation date verify failed");
      gnutls_x509_crt_deinit(x509_cert);
      return CURLE_SSL_CONNECT_ERROR;
    }