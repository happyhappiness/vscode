{
    /* TODO s/data->set.ssl.enable_beast/SSL_SET_OPTION(enable_beast)/g */
    SSLSetSessionOption(connssl->ssl_ctx, kSSLSessionOptionSendOneByteRecord,
                      !data->set.ssl.enable_beast);
    SSLSetSessionOption(connssl->ssl_ctx, kSSLSessionOptionFalseStart,
                      data->set.ssl.falsestart); /* false start support */
  }