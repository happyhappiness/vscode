{
#if defined(HTTPS_PROXY_SUPPORT)
    conn->proxy_ssl[sockindex] = conn->ssl[sockindex];
    memset(&conn->ssl[sockindex], 0, sizeof(conn->ssl[sockindex]));
#else
    return CURLE_NOT_BUILT_IN;
#endif
  }