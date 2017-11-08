static const char *
get_ssl_version_txt(SSL *ssl)
{
  if(!ssl)
    return "";

  switch(SSL_version(ssl)) {
#if OPENSSL_VERSION_NUMBER >= 0x1000100FL
  case TLS1_2_VERSION:
    return "TLSv1.2";
  case TLS1_1_VERSION:
    return "TLSv1.1";
#endif
  case TLS1_VERSION:
    return "TLSv1.0";
  case SSL3_VERSION:
    return "SSLv3";
  case SSL2_VERSION:
    return "SSLv2";
  }
  return "unknown";
}