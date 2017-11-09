static CURLcode nss_init_sslver(SSLVersionRange *sslver,
                                struct Curl_easy *data,
                                struct connectdata *conn)
{
  CURLcode result;
  const long min = SSL_CONN_CONFIG(version);
  const long max = SSL_CONN_CONFIG(version_max);

  /* map CURL_SSLVERSION_DEFAULT to NSS default */
  if(min == CURL_SSLVERSION_DEFAULT || max == CURL_SSLVERSION_MAX_DEFAULT) {
    /* map CURL_SSLVERSION_DEFAULT to NSS default */
    if(SSL_VersionRangeGetDefault(ssl_variant_stream, sslver) != SECSuccess)
      return CURLE_SSL_CONNECT_ERROR;
    /* ... but make sure we use at least TLSv1.0 according to libcurl API */
    if(sslver->min < SSL_LIBRARY_VERSION_TLS_1_0)
      sslver->min = SSL_LIBRARY_VERSION_TLS_1_0;
  }

  switch(min) {
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

  switch(max) {
  case CURL_SSLVERSION_MAX_NONE:
  case CURL_SSLVERSION_MAX_DEFAULT:
    break;
  default:
    result = nss_sslver_from_curl(&sslver->max, max >> 16);
    if(result) {
      failf(data, "unsupported max version passed via CURLOPT_SSLVERSION");
      return result;
    }
  }

  return CURLE_OK;
}