int
curl_dogetaddrinfo(const char *hostname,
                   const char *service,
                   const struct addrinfo *hints,
                   struct addrinfo **result,
                   int line, const char *source)
{
#ifdef USE_LWIPSOCK
  int res = lwip_getaddrinfo(hostname, service, hints, result);
#else
  int res = (getaddrinfo)(hostname, service, hints, result);
#endif
  if(0 == res)
    /* success */
    curl_memlog("ADDR %s:%d getaddrinfo() = %p\n",
                source, line, (void *)*result);
  else
    curl_memlog("ADDR %s:%d getaddrinfo() failed\n",
                source, line);
  return res;
}