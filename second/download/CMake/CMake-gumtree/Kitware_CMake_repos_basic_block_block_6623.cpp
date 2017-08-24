{
    failf(data, "can't pass a custom cipher list to older GnuTLS"
          " versions");
    return CURLE_SSL_CONNECT_ERROR;
  }