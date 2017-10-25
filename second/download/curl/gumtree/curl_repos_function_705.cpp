int
Curl_inet_pton(int af, const char *src, void *dst)
{
  switch (af) {
  case AF_INET:
    return (inet_pton4(src, (unsigned char *)dst));
#ifdef ENABLE_IPV6
#ifndef AF_INET6
#define AF_INET6        (AF_MAX+1)        /* just to let this compile */
#endif
  case AF_INET6:
    return (inet_pton6(src, (unsigned char *)dst));
#endif
  default:
    errno = EAFNOSUPPORT;
    return (-1);
  }
  /* NOTREACHED */
}