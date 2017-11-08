static CURLcode
set_ssl_version_min_max(unsigned int *protoflags, struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  long ssl_version = SSL_CONN_CONFIG(version);
  long ssl_version_max = SSL_CONN_CONFIG(version_max);
  long i = ssl_version;
  switch(ssl_version_max) {
    case CURL_SSLVERSION_MAX_NONE:
      ssl_version_max = ssl_version;
      break;
    case CURL_SSLVERSION_MAX_DEFAULT:
      ssl_version_max = CURL_SSLVERSION_TLSv1_2;
      break;
  }
  for(; i <= (ssl_version_max >> 16); ++i) {
    switch(i) {
      case CURL_SSLVERSION_TLSv1_0:
        *protoflags |= CURL_GSKPROTO_TLSV10_MASK;
        break;
      case CURL_SSLVERSION_TLSv1_1:
        *protoflags |= CURL_GSKPROTO_TLSV11_MASK;
        break;
      case CURL_SSLVERSION_TLSv1_2:
        *protoflags |= CURL_GSKPROTO_TLSV11_MASK;
        break;
      case CURL_SSLVERSION_TLSv1_3:
        failf(data, "GSKit: TLS 1.3 is not yet supported");
        return CURLE_SSL_CONNECT_ERROR;
    }
  }

  return CURLE_OK;
}