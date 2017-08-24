{
      failf(data, "schannel: failed to retrieve ALPN result");
      return CURLE_SSL_CONNECT_ERROR;
    }