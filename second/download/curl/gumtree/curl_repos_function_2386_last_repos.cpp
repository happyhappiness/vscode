static CURLcode
set_ssl_version_min_max(long *ctx_options, struct connectdata *conn,
                        int sockindex)
{
#if (OPENSSL_VERSION_NUMBER < 0x1000100FL) || !defined(TLS1_3_VERSION)
  /* convoluted #if condition just to avoid compiler warnings on unused
     variable */
  struct Curl_easy *data = conn->data;
#endif
  long ssl_version = SSL_CONN_CONFIG(version);
  long ssl_version_max = SSL_CONN_CONFIG(version_max);

  if(ssl_version_max == CURL_SSLVERSION_MAX_NONE) {
    ssl_version_max = ssl_version << 16;
  }

  switch(ssl_version) {
    case CURL_SSLVERSION_TLSv1_3:
#ifdef TLS1_3_VERSION
    {
      struct ssl_connect_data *connssl = &conn->ssl[sockindex];
      SSL_CTX_set_max_proto_version(BACKEND->ctx, TLS1_3_VERSION);
      *ctx_options |= SSL_OP_NO_TLSv1_2;
    }
#else
      (void)sockindex;
      failf(data, OSSL_PACKAGE " was built without TLS 1.3 support");
      return CURLE_NOT_BUILT_IN;
#endif
      /* FALLTHROUGH */
    case CURL_SSLVERSION_TLSv1_2:
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
      *ctx_options |= SSL_OP_NO_TLSv1_1;
#else
      failf(data, OSSL_PACKAGE " was built without TLS 1.2 support");
      return CURLE_NOT_BUILT_IN;
#endif
      /* FALLTHROUGH */
    case CURL_SSLVERSION_TLSv1_1:
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
      *ctx_options |= SSL_OP_NO_TLSv1;
#else
      failf(data, OSSL_PACKAGE " was built without TLS 1.1 support");
      return CURLE_NOT_BUILT_IN;
#endif
      /* FALLTHROUGH */
    case CURL_SSLVERSION_TLSv1_0:
      *ctx_options |= SSL_OP_NO_SSLv2;
      *ctx_options |= SSL_OP_NO_SSLv3;
      break;
  }

  switch(ssl_version_max) {
    case CURL_SSLVERSION_MAX_TLSv1_0:
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
      *ctx_options |= SSL_OP_NO_TLSv1_1;
#endif
      /* FALLTHROUGH */
    case CURL_SSLVERSION_MAX_TLSv1_1:
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
      *ctx_options |= SSL_OP_NO_TLSv1_2;
#endif
      /* FALLTHROUGH */
    case CURL_SSLVERSION_MAX_TLSv1_2:
    case CURL_SSLVERSION_MAX_DEFAULT:
#ifdef TLS1_3_VERSION
      *ctx_options |= SSL_OP_NO_TLSv1_3;
#endif
      break;
    case CURL_SSLVERSION_MAX_TLSv1_3:
#ifdef TLS1_3_VERSION
      break;
#else
      failf(data, OSSL_PACKAGE " was built without TLS 1.3 support");
      return CURLE_NOT_BUILT_IN;
#endif
  }
  return CURLE_OK;
}