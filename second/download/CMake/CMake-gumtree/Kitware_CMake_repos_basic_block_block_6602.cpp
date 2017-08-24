{
  struct Curl_easy *data = conn->data;
  long ssl_version = SSL_CONN_CONFIG(version);
  long ssl_version_max = SSL_CONN_CONFIG(version_max);
  long i = ssl_version;
  long protocol_priority_idx = 0;

  switch(ssl_version_max) {
    case CURL_SSLVERSION_MAX_NONE:
      ssl_version_max = ssl_version << 16;
      break;
    case CURL_SSLVERSION_MAX_DEFAULT:
      ssl_version_max = CURL_SSLVERSION_MAX_TLSv1_2;
      break;
  }

  for(; i <= (ssl_version_max >> 16) &&
        protocol_priority_idx < list_size; ++i) {
    switch(i) {
      case CURL_SSLVERSION_TLSv1_0:
        protocol_priority[protocol_priority_idx++] = GNUTLS_TLS1_0;
        break;
      case CURL_SSLVERSION_TLSv1_1:
        protocol_priority[protocol_priority_idx++] = GNUTLS_TLS1_1;
        break;
      case CURL_SSLVERSION_TLSv1_2:
        protocol_priority[protocol_priority_idx++] = GNUTLS_TLS1_2;
        break;
      case CURL_SSLVERSION_TLSv1_3:
        failf(data, "GnuTLS: TLS 1.3 is not yet supported");
        return CURLE_SSL_CONNECT_ERROR;
    }
  }
  return CURLE_OK;
}