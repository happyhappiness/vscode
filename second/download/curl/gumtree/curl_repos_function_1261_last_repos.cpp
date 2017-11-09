curl_socket_t curl_accept(curl_socket_t s, void *saddr, void *saddrlen,
                          int line, const char *source)
{
  const char *fmt = (sizeof(curl_socket_t) == sizeof(int)) ?
    "FD %s:%d accept() = %d\n" :
    (sizeof(curl_socket_t) == sizeof(long)) ?
    "FD %s:%d accept() = %ld\n" :
    "FD %s:%d accept() = %zd\n";

  struct sockaddr *addr = (struct sockaddr *)saddr;
  curl_socklen_t *addrlen = (curl_socklen_t *)saddrlen;

  curl_socket_t sockfd = accept(s, addr, addrlen);

  if(source && (sockfd != CURL_SOCKET_BAD))
    curl_memlog(fmt, source, line, sockfd);

  return sockfd;
}