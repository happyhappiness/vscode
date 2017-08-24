{
      failf(data, "SSL: SSLSetSessionOption() failed: OSStatus %d", err);
      return CURLE_SSL_CONNECT_ERROR;
    }