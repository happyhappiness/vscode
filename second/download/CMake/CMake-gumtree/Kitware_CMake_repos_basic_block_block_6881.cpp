h(min) {
  case CURL_SSLVERSION_DEFAULT:
    break;
  case CURL_SSLVERSION_TLSv1:
    sslver->min = SSL_LIBRARY_VERSION_TLS_1_0;
    break;
  default:
    result = nss_sslver_from_curl(&sslver->min, min);
    if(result) {
      failf(data, "unsupported min version passed via CURLOPT_SSLVERSION");
      return result;
    }
    if(max == CURL_SSLVERSION_MAX_NONE)
      sslver->max = sslver->min;
  }