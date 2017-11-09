static CURLcode
set_ssl_version_min_max(const char **prioritylist, struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  long ssl_version = SSL_CONN_CONFIG(version);
  long ssl_version_max = SSL_CONN_CONFIG(version_max);
  if(ssl_version == CURL_SSLVERSION_TLSv1_3 ||
     ssl_version_max == CURL_SSLVERSION_MAX_TLSv1_3) {
    failf(data, "GnuTLS: TLS 1.3 is not yet supported");
    return CURLE_SSL_CONNECT_ERROR;
  }
  if(ssl_version_max == CURL_SSLVERSION_MAX_NONE) {
    ssl_version_max = ssl_version << 16;
  }
  switch(ssl_version | ssl_version_max) {
    case CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_TLSv1_0:
      *prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                      "+VERS-TLS1.0:" GNUTLS_SRP;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_TLSv1_1:
      *prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                      "+VERS-TLS1.0:+VERS-TLS1.1:" GNUTLS_SRP;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_TLSv1_2:
    case CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_DEFAULT:
      *prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                      "+VERS-TLS1.0:+VERS-TLS1.1:+VERS-TLS1.2:" GNUTLS_SRP;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_1 | CURL_SSLVERSION_MAX_TLSv1_1:
      *prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                      "+VERS-TLS1.1:" GNUTLS_SRP;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_1 | CURL_SSLVERSION_MAX_TLSv1_2:
    case CURL_SSLVERSION_TLSv1_1 | CURL_SSLVERSION_MAX_DEFAULT:
      *prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                      "+VERS-TLS1.1:+VERS-TLS1.2:" GNUTLS_SRP;
      return CURLE_OK;
    case CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_TLSv1_2:
    case CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT:
      *prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                      "+VERS-TLS1.2:" GNUTLS_SRP;
      return CURLE_OK;
  }

  failf(data, "GnuTLS: cannot set ssl protocol");
  return CURLE_SSL_CONNECT_ERROR;
}