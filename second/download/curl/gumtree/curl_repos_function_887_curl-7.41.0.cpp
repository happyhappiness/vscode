static bool getaddressinfo(struct sockaddr* sa, char* addr,
                           long* port)
{
  unsigned short us_port;
  struct sockaddr_in* si = NULL;
#ifdef ENABLE_IPV6
  struct sockaddr_in6* si6 = NULL;
#endif
#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)
  struct sockaddr_un* su = NULL;
#endif

  switch (sa->sa_family) {
    case AF_INET:
      si = (struct sockaddr_in*) sa;
      if(Curl_inet_ntop(sa->sa_family, &si->sin_addr,
                        addr, MAX_IPADR_LEN)) {
        us_port = ntohs(si->sin_port);
        *port = us_port;
        return TRUE;
      }
      break;
#ifdef ENABLE_IPV6
    case AF_INET6:
      si6 = (struct sockaddr_in6*)sa;
      if(Curl_inet_ntop(sa->sa_family, &si6->sin6_addr,
                        addr, MAX_IPADR_LEN)) {
        us_port = ntohs(si6->sin6_port);
        *port = us_port;
        return TRUE;
      }
      break;
#endif
#if defined(HAVE_SYS_UN_H) && defined(AF_UNIX)
    case AF_UNIX:
      su = (struct sockaddr_un*)sa;
      snprintf(addr, MAX_IPADR_LEN, "%s", su->sun_path);
      *port = 0;
      return TRUE;
#endif
    default:
      break;
  }

  addr[0] = '\0';
  *port = 0;

  return FALSE;
}