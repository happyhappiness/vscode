Curl_addrinfo *Curl_str2addr(char *address, int port)
{
  struct in_addr in;
  if(Curl_inet_pton(AF_INET, address, &in) > 0)
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(AF_INET, &in, address, port);
#ifdef ENABLE_IPV6
  else {
    struct in6_addr in6;
    if(Curl_inet_pton(AF_INET6, address, &in6) > 0)
      /* This is a dotted IPv6 address ::1-style */
      return Curl_ip2addr(AF_INET6, &in6, address, port);
  }
#endif
  return NULL; /* bad input format */
}