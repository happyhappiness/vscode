static ssize_t Curl_gtls_pull(void *s, void *buf, size_t len)
{
  ssize_t ret = sread(GNUTLS_POINTER_TO_INT_CAST(s), buf, len);
#if defined(USE_WINSOCK) && !defined(GNUTLS_MAPS_WINSOCK_ERRORS)
  if(ret < 0)
    gnutls_transport_set_global_errno(gtls_mapped_sockerrno());
#endif
  return ret;
}