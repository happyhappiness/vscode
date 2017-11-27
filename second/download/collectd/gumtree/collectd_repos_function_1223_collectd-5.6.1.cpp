static char *
niptoha(const tChrony_IPAddr * addr, char *p_buf, size_t p_buf_size)
{
  int rc = 1;
  unsigned long a, b, c, d, ip;

  switch (ntohs(addr->f_family))
  {
  case IPADDR_UNSPEC:
    rc = snprintf(p_buf, p_buf_size, "[UNSPEC]");
    break;
  case IPADDR_INET4:
    ip = ntohl(addr->addr.ip4);
    a = (ip >> 24) & 0xff;
    b = (ip >> 16) & 0xff;
    c = (ip >> 8) & 0xff;
    d = (ip >> 0) & 0xff;
    rc = snprintf(p_buf, p_buf_size, "%ld.%ld.%ld.%ld", a, b, c, d);
    break;
  case IPADDR_INET6:
  {
    const char *rp = inet_ntop(AF_INET6, addr->addr.ip6, p_buf, p_buf_size);
    if (rp == NULL)
    {
      ERROR(PLUGIN_NAME ": Error converting ipv6 address to string. Errno = %d", errno);
      rc = snprintf(p_buf, p_buf_size, "[UNKNOWN]");
    }
    break;
  }
  default:
    rc = snprintf(p_buf, p_buf_size, "[UNKNOWN]");
  }
  assert(rc > 0);
  return p_buf;
}