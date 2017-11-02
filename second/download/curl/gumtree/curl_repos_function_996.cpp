Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                const char *hostname,
                                int port,
                                int *waitp)
{
  return Curl_resolver_getaddrinfo(conn, hostname, port, waitp);
}