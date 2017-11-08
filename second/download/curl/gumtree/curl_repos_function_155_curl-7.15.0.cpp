static curl_socket_t mksock(bool use_ipv6)
{
  curl_socket_t sock;
#ifdef ENABLE_IPV6
  if(!use_ipv6)
#else
    (void)use_ipv6;
#endif
  sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef ENABLE_IPV6
  else
    sock = socket(AF_INET6, SOCK_STREAM, 0);
#endif

  if (sock < 0) {
    perror("opening stream socket");
    logmsg("Error opening socket");
    return CURL_SOCKET_BAD;
  }

  return sock;
}