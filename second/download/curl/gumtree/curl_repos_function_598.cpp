static bool socket_domain_is_ip(void)
{
  switch(socket_domain) {
  case AF_INET:
#ifdef ENABLE_IPV6
  case AF_INET6:
#endif
    return true;
  default:
  /* case AF_UNIX: */
    return false;
  }
}