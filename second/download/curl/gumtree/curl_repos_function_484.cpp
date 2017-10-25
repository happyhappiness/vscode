const char *Curl_printable_address(const Curl_addrinfo *ip,
                                   char *buf, size_t bufsize)
{
  const void *ip4 = &((const struct sockaddr_in*)ip->ai_addr)->sin_addr;
  int af = ip->ai_family;
#ifdef CURLRES_IPV6
  const void *ip6 = &((const struct sockaddr_in6*)ip->ai_addr)->sin6_addr;
#else
  const void *ip6 = NULL;
#endif

  return Curl_inet_ntop(af, af == AF_INET ? ip4 : ip6, buf, bufsize);
}