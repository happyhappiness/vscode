Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                const char *hostname,
                                int port,
                                int *waitp)
{
  Curl_addrinfo *ai = NULL;

#ifdef CURL_DISABLE_VERBOSE_STRINGS
  (void)conn;
#endif

  *waitp = 0; /* synchronous response only */

  ai = Curl_ipv4_resolve_r(hostname, port);
  if(!ai)
    infof(conn->data, "Curl_ipv4_resolve_r failed for %s\n", hostname);

  return ai;
}