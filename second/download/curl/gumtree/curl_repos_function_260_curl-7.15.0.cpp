Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                char *hostname,
                                int port,
                                int *waitp)
{
  struct hostent *h = NULL;
  struct SessionHandle *data = conn->data;
  in_addr_t in;

  *waitp = 0; /* don't wait, we act synchronously */

  in = inet_addr(hostname);
  if (in != CURL_INADDR_NONE)
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(in, hostname, port);

  /* fire up a new resolver thread! */
  if (init_resolve_thread(conn, hostname, port, NULL)) {
    *waitp = TRUE;  /* please wait for the response */
    return NULL;
  }

  /* fall-back to blocking version */
  infof(data, "init_resolve_thread() failed for %s; %s\n",
        hostname, Curl_strerror(conn,GetLastError()));

  h = gethostbyname(hostname);
  if (!h) {
    infof(data, "gethostbyname(2) failed for %s:%d; %s\n",
          hostname, port, Curl_strerror(conn,WSAGetLastError()));
    return NULL;
  }
  return Curl_he2ai(h, port);
}