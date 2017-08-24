{
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      ssl_version = CURL_SSLVERSION_TLSv1_0;
      ssl_version_max = CURL_SSLVERSION_MAX_TLSv1_2;
      break;
  }