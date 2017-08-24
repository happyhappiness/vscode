{
#endif /* CURL_BUILD_MAC */
    bool break_on_auth = !conn->ssl_config.verifypeer || ssl_cafile;
    err = SSLSetSessionOption(connssl->ssl_ctx,
                              kSSLSessionOptionBreakOnServerAuth,
                              break_on_auth);
    if(err != noErr) {
      failf(data, "SSL: SSLSetSessionOption() failed: OSStatus %d", err);
      return CURLE_SSL_CONNECT_ERROR;
    }
  }