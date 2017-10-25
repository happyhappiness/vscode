Curl_addrinfo *Curl_getaddrinfo(struct connectdata *conn,
                                char *hostname,
                                int port,
                                int *waitp)
{
  char *bufp;
  struct SessionHandle *data = conn->data;
  in_addr_t in = inet_addr(hostname);

  *waitp = FALSE;

  if (in != CURL_INADDR_NONE) {
    /* This is a dotted IP address 123.123.123.123-style */
    return Curl_ip2addr(in, hostname, port);
  }

  bufp = strdup(hostname);

  if(bufp) {
    Curl_safefree(conn->async.hostname);
    conn->async.hostname = bufp;
    conn->async.port = port;
    conn->async.done = FALSE; /* not done */
    conn->async.status = 0;   /* clear */
    conn->async.dns = NULL;   /* clear */

    /* areschannel is already setup in the Curl_open() function */
    ares_gethostbyname(data->state.areschannel, hostname, PF_INET,
                       (ares_host_callback)Curl_addrinfo4_callback, conn);

    *waitp = TRUE; /* please wait for the response */
  }
  return NULL; /* no struct yet */
}