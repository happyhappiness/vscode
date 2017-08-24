h(i) {
        case CURL_SSLVERSION_TLSv1_0:
          (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                            kTLSProtocol1,
                                            true);
          break;
        case CURL_SSLVERSION_TLSv1_1:
          (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                            kTLSProtocol11,
                                            true);
          break;
        case CURL_SSLVERSION_TLSv1_2:
          (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                            kTLSProtocol12,
                                            true);
          break;
        case CURL_SSLVERSION_TLSv1_3:
          failf(data, "DarwinSSL: TLS 1.3 is not yet supported");
          return CURLE_SSL_CONNECT_ERROR;
      }