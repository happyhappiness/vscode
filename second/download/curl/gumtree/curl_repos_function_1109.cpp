curl_socket_t curl_socket(int domain, int type, int protocol,
                          int line, const char *source)
{
  const char *fmt = (sizeof(curl_socket_t) == sizeof(int)) ?
                    "FD %s:%d socket() = %d\n" :
                    (sizeof(curl_socket_t) == sizeof(long)) ?
                    "FD %s:%d socket() = %ld\n" :
                    "FD %s:%d socket() = %zd\n" ;

  curl_socket_t sockfd = socket(domain, type, protocol);

  if(source && (sockfd != CURL_SOCKET_BAD))
    curl_memlog(fmt, source, line, sockfd);

  return sockfd;
}