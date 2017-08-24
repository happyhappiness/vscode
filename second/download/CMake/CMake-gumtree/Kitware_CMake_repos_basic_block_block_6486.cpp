{
#if CURL_SUPPORT_MAC_10_8
    (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                       kSSLProtocolAll,
                                       false);
    switch(conn->ssl_config.version) {
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                         kTLSProtocol1,
                                         true);
      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                         kTLSProtocol11,
                                         true);
      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                         kTLSProtocol12,
                                         true);
      break;
    case CURL_SSLVERSION_TLSv1_0:
    case CURL_SSLVERSION_TLSv1_1:
    case CURL_SSLVERSION_TLSv1_2:
    case CURL_SSLVERSION_TLSv1_3:
      {
        CURLcode result = set_ssl_version_min_max(conn, sockindex);
        if(result != CURLE_OK)
          return result;
        break;
      }
    case CURL_SSLVERSION_SSLv3:
      err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                         kSSLProtocol3,
                                         true);
      if(err != noErr) {
        failf(data, "Your version of the OS does not support SSLv3");
        return CURLE_SSL_CONNECT_ERROR;
      }
      break;
    case CURL_SSLVERSION_SSLv2:
      err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                         kSSLProtocol2,
                                         true);
      if(err != noErr) {
        failf(data, "Your version of the OS does not support SSLv2");
        return CURLE_SSL_CONNECT_ERROR;
      }
      break;
    default:
      failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
      return CURLE_SSL_CONNECT_ERROR;
    }
#endif  /* CURL_SUPPORT_MAC_10_8 */
  }