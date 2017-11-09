static CURLcode mbedtls_version_from_curl(int *mbedver, long version)
{
  switch(version) {
    case CURL_SSLVERSION_TLSv1_0:
      *mbedver = MBEDTLS_SSL_MINOR_VERSION_1;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_1:
      *mbedver = MBEDTLS_SSL_MINOR_VERSION_2;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_2:
      *mbedver = MBEDTLS_SSL_MINOR_VERSION_3;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_3:
      break;
  }
  return CURLE_SSL_CONNECT_ERROR;
}