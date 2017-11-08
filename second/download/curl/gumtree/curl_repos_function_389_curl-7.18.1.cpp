CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
                          const struct Curl_dns_entry *remotehost,
                          curl_socket_t *sockconn,   /* the connected socket */
                          Curl_addrinfo **addr,      /* the one we used */
                          bool *connected)           /* really connected? */
{
  struct SessionHandle *data = conn->data;
  curl_socket_t sockfd = CURL_SOCKET_BAD;
  int aliasindex;
  int num_addr;
  Curl_addrinfo *ai;
  Curl_addrinfo *curr_addr;

  struct timeval after;
  struct timeval before = Curl_tvnow();

  /*************************************************************
   * Figure out what maximum time we have left
   *************************************************************/
  long timeout_ms;
  long timeout_per_addr;

  *connected = FALSE; /* default to not connected */

  /* get the timeout left */
  timeout_ms = Curl_timeleft(conn, &before, TRUE);

  if(timeout_ms < 0) {
    /* a precaution, no need to continue if time already is up */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }
  Curl_expire(data, timeout_ms);

  /* Max time for each address */
  num_addr = Curl_num_addresses(remotehost->addr);
  timeout_per_addr = timeout_ms / num_addr;

  ai = remotehost->addr;

  /* Below is the loop that attempts to connect to all IP-addresses we
   * know for the given host. One by one until one IP succeeds.
   */

  if(data->state.used_interface == Curl_if_multi)
    /* don't hang when doing multi */
    timeout_per_addr = 0;

  /*
   * Connecting with a Curl_addrinfo chain
   */
  for (curr_addr = ai, aliasindex=0; curr_addr;
       curr_addr = curr_addr->ai_next, aliasindex++) {

    /* start connecting to the IP curr_addr points to */
    sockfd = singleipconnect(conn, curr_addr, timeout_per_addr, connected);

    if(sockfd != CURL_SOCKET_BAD)
      break;

    /* get a new timeout for next attempt */
    after = Curl_tvnow();
    timeout_ms -= Curl_tvdiff(after, before);
    if(timeout_ms < 0) {
      failf(data, "connect() timed out!");
      return CURLE_OPERATION_TIMEDOUT;
    }
    before = after;
  }  /* end of connect-to-each-address loop */

  if(sockfd == CURL_SOCKET_BAD) {
    /* no good connect was made */
    *sockconn = CURL_SOCKET_BAD;
    failf(data, "couldn't connect to host");
    return CURLE_COULDNT_CONNECT;
  }

  /* leave the socket in non-blocking mode */

  /* store the address we use */
  if(addr)
    *addr = curr_addr;

  /* allow NULL-pointers to get passed in */
  if(sockconn)
    *sockconn = sockfd;    /* the socket descriptor we've connected */

  data->info.numconnects++; /* to track the number of connections made */

  return CURLE_OK;
}