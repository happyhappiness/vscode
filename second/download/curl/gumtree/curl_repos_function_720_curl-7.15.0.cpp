bool Curl_ipvalid(struct SessionHandle *data)
{
  if(data->set.ip_version == CURL_IPRESOLVE_V6) {
    /* see if we have an IPv6 stack */
    curl_socket_t s = socket(PF_INET6, SOCK_DGRAM, 0);
    if (s == CURL_SOCKET_BAD)
      /* an ipv6 address was requested and we can't get/use one */
      return FALSE;
    sclose(s);
  }
  return TRUE;
}