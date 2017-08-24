{
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol1);
      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol12);
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
      err = SSLSetProtocolVersionMin(connssl->ssl_ctx, kSSLProtocol3);
      if(err != noErr) {
        failf(data, "Your version of the OS does not support SSLv3");
        return CURLE_SSL_CONNECT_ERROR;
      }
      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kSSLProtocol3);
      break;
    case CURL_SSLVERSION_SSLv2:
      err = SSLSetProtocolVersionMin(connssl->ssl_ctx, kSSLProtocol2);
      if(err != noErr) {
        failf(data, "Your version of the OS does not support SSLv2");
        return CURLE_SSL_CONNECT_ERROR;
      }
      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kSSLProtocol2);
      break;
    default:
      failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
      return CURLE_SSL_CONNECT_ERROR;
    }