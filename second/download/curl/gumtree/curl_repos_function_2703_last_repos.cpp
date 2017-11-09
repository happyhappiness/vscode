static ssize_t Curl_gtls_push(void *s, const void *buf, size_t len)
{
  ssize_t ret = swrite(GNUTLS_POINTER_TO_SOCKET_CAST(s), buf, len);
#if defined(USE_WINSOCK) && !defined(GNUTLS_MAPS_WINSOCK_ERRORS)
  if(ret < 0)
    gnutls_transport_set_global_errno(gtls_mapped_sockerrno());
#endif
  return ret;
}