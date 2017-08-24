f(err != noErr) {
    failf(data, "SSL: SSLSetConnection() failed: %d", err);
    return CURLE_SSL_CONNECT_ERROR;
  }