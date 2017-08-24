{
  case CURL_SSLVERSION_TLSv1:
    /* TODO: set sslver->max to SSL_LIBRARY_VERSION_TLS_1_3 once stable */
#ifdef SSL_LIBRARY_VERSION_TLS_1_2
    *nssver = SSL_LIBRARY_VERSION_TLS_1_2;
#elif defined SSL_LIBRARY_VERSION_TLS_1_1
    *nssver = SSL_LIBRARY_VERSION_TLS_1_1;
#else
    *nssver = SSL_LIBRARY_VERSION_TLS_1_0;
#endif
    return CURLE_OK;

  case CURL_SSLVERSION_SSLv2:
    *nssver = SSL_LIBRARY_VERSION_2;
    return CURLE_OK;

  case CURL_SSLVERSION_SSLv3:
    *nssver = SSL_LIBRARY_VERSION_3_0;
    return CURLE_OK;

  case CURL_SSLVERSION_TLSv1_0:
    *nssver = SSL_LIBRARY_VERSION_TLS_1_0;
    return CURLE_OK;

  case CURL_SSLVERSION_TLSv1_1:
#ifdef SSL_LIBRARY_VERSION_TLS_1_1
    *nssver = SSL_LIBRARY_VERSION_TLS_1_1;
    return CURLE_OK;
#else
    return CURLE_SSL_CONNECT_ERROR;
#endif

  case CURL_SSLVERSION_TLSv1_2:
#ifdef SSL_LIBRARY_VERSION_TLS_1_2
    *nssver = SSL_LIBRARY_VERSION_TLS_1_2;
    return CURLE_OK;
#else
    return CURLE_SSL_CONNECT_ERROR;
#endif

  case CURL_SSLVERSION_TLSv1_3:
#ifdef SSL_LIBRARY_VERSION_TLS_1_3
    *nssver = SSL_LIBRARY_VERSION_TLS_1_3;
    return CURLE_OK;
#else
    return CURLE_SSL_CONNECT_ERROR;
#endif

  default:
    return CURLE_SSL_CONNECT_ERROR;
  }