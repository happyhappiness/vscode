int curl_socketpair(int domain, int type, int protocol,
                    curl_socket_t socket_vector[2],
                    int line, const char *source)
{
  const char *fmt = (sizeof(curl_socket_t) == sizeof(int)) ?
    "FD %s:%d socketpair() = %d %d\n" :
    (sizeof(curl_socket_t) == sizeof(long)) ?
    "FD %s:%d socketpair() = %ld %ld\n" :
    "FD %s:%d socketpair() = %zd %zd\n";

  int res = socketpair(domain, type, protocol, socket_vector);

  if(source && (0 == res))
    curl_memlog(fmt, source, line, socket_vector[0], socket_vector[1]);

  return res;
}