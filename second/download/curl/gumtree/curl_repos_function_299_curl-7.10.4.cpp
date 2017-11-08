void Curl_freeaddrinfo(Curl_addrinfo *p)
{
#ifdef ENABLE_IPV6
  freeaddrinfo(p);
#else
  free(p);
#endif
}