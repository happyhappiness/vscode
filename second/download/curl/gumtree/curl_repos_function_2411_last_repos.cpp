static CURLcode
set_ssl_version_min_max(struct connectdata *conn, int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  int mbedtls_ver_min = MBEDTLS_SSL_MINOR_VERSION_1;
  int mbedtls_ver_max = MBEDTLS_SSL_MINOR_VERSION_1;
  long ssl_version = SSL_CONN_CONFIG(version);
  long ssl_version_max = SSL_CONN_CONFIG(version_max);
  CURLcode result = CURLE_OK;

  switch(ssl_version) {
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      ssl_version = CURL_SSLVERSION_TLSv1_0;
      ssl_version_max = CURL_SSLVERSION_MAX_TLSv1_2;
      break;
  }

  switch(ssl_version_max) {
    case CURL_SSLVERSION_MAX_NONE:
      ssl_version_max = ssl_version << 16;
      break;
    case CURL_SSLVERSION_MAX_DEFAULT:
      ssl_version_max = CURL_SSLVERSION_MAX_TLSv1_2;
      break;
  }

  result = mbedtls_version_from_curl(&mbedtls_ver_min, ssl_version);
  if(result) {
    failf(data, "unsupported min version passed via CURLOPT_SSLVERSION");
    return result;
  }
  result = mbedtls_version_from_curl(&mbedtls_ver_max, ssl_version_max >> 16);
  if(result) {
    failf(data, "unsupported max version passed via CURLOPT_SSLVERSION");
    return result;
  }

  mbedtls_ssl_conf_min_version(&BACKEND->config, MBEDTLS_SSL_MAJOR_VERSION_3,
                               mbedtls_ver_min);
  mbedtls_ssl_conf_max_version(&BACKEND->config, MBEDTLS_SSL_MAJOR_VERSION_3,
                               mbedtls_ver_max);

  return result;
}