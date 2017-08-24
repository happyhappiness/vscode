{
    failf(data, "GnuTLS does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }