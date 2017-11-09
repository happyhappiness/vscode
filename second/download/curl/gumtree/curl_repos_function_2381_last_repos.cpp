static const char *tls_rt_type(int type)
{
  switch(type) {
#ifdef SSL3_RT_HEADER
  case SSL3_RT_HEADER:
    return "TLS header";
#endif
  case SSL3_RT_CHANGE_CIPHER_SPEC:
    return "TLS change cipher";
  case SSL3_RT_ALERT:
    return "TLS alert";
  case SSL3_RT_HANDSHAKE:
    return "TLS handshake";
  case SSL3_RT_APPLICATION_DATA:
    return "TLS app data";
  default:
    return "TLS Unknown";
  }
}