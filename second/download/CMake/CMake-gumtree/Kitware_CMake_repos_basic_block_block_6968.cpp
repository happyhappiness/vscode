h(SSL_CONN_CONFIG(version)) {
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    ssl_set_min_version(&connssl->ssl, SSL_MAJOR_VERSION_3,
                        SSL_MINOR_VERSION_1);
    break;
  case CURL_SSLVERSION_SSLv3:
    ssl_set_min_version(&connssl->ssl, SSL_MAJOR_VERSION_3,
                        SSL_MINOR_VERSION_0);
    ssl_set_max_version(&connssl->ssl, SSL_MAJOR_VERSION_3,
                        SSL_MINOR_VERSION_0);
    infof(data, "PolarSSL: Forced min. SSL Version to be SSLv3\n");
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
  default:
    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
    return CURLE_SSL_CONNECT_ERROR;
  }