static CURLcode
set_ssl_version_min_max(struct connectdata *conn, int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  long ssl_version = SSL_CONN_CONFIG(version);
  long ssl_version_max = SSL_CONN_CONFIG(version_max);

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

#if CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS
  if(SSLSetProtocolVersionMax != NULL) {
    SSLProtocol darwin_ver_min = kTLSProtocol1;
    SSLProtocol darwin_ver_max = kTLSProtocol1;
    CURLcode result = darwinssl_version_from_curl(&darwin_ver_min,
                                                  ssl_version);
    if(result) {
      failf(data, "unsupported min version passed via CURLOPT_SSLVERSION");
      return result;
    }
    result = darwinssl_version_from_curl(&darwin_ver_max,
                                         ssl_version_max >> 16);
    if(result) {
      failf(data, "unsupported max version passed via CURLOPT_SSLVERSION");
      return result;
    }

    (void)SSLSetProtocolVersionMin(BACKEND->ssl_ctx, darwin_ver_min);
    (void)SSLSetProtocolVersionMax(BACKEND->ssl_ctx, darwin_ver_max);
    return result;
  }
  else {
#if CURL_SUPPORT_MAC_10_8
    long i = ssl_version;
    (void)SSLSetProtocolVersionEnabled(BACKEND->ssl_ctx,
                                       kSSLProtocolAll,
                                       false);
    for(; i <= (ssl_version_max >> 16); i++) {
      switch(i) {
        case CURL_SSLVERSION_TLSv1_0:
          (void)SSLSetProtocolVersionEnabled(BACKEND->ssl_ctx,
                                            kTLSProtocol1,
                                            true);
          break;
        case CURL_SSLVERSION_TLSv1_1:
          (void)SSLSetProtocolVersionEnabled(BACKEND->ssl_ctx,
                                            kTLSProtocol11,
                                            true);
          break;
        case CURL_SSLVERSION_TLSv1_2:
          (void)SSLSetProtocolVersionEnabled(BACKEND->ssl_ctx,
                                            kTLSProtocol12,
                                            true);
          break;
        case CURL_SSLVERSION_TLSv1_3:
          failf(data, "DarwinSSL: TLS 1.3 is not yet supported");
          return CURLE_SSL_CONNECT_ERROR;
      }
    }
    return CURLE_OK;
#endif  /* CURL_SUPPORT_MAC_10_8 */
  }
#endif  /* CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS */
  failf(data, "DarwinSSL: cannot set SSL protocol");
  return CURLE_SSL_CONNECT_ERROR;
}