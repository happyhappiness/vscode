CURLcode Curl_connecthost(struct connectdata *conn,  /* context */
                          const struct Curl_dns_entry *remotehost)
{
  struct SessionHandle *data = conn->data;
  struct timeval before = Curl_tvnow();
  CURLcode result = CURLE_COULDNT_CONNECT;

  long timeout_ms = Curl_timeleft(data, &before, TRUE);

  if(timeout_ms < 0) {
    /* a precaution, no need to continue if time already is up */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  conn->num_addr = Curl_num_addresses(remotehost->addr);
  conn->tempaddr[0] = remotehost->addr;
  conn->tempaddr[1] = NULL;
  conn->tempsock[0] = CURL_SOCKET_BAD;
  conn->tempsock[1] = CURL_SOCKET_BAD;
  Curl_expire(conn->data, HAPPY_EYEBALLS_TIMEOUT);

  /* Max time for the next connection attempt */
  conn->timeoutms_per_addr =
    conn->tempaddr[0]->ai_next == NULL ? timeout_ms : timeout_ms / 2;

  /* start connecting to first IP */
  while(conn->tempaddr[0]) {
    result = singleipconnect(conn, conn->tempaddr[0], &(conn->tempsock[0]));
    if(!result)
      break;
    conn->tempaddr[0] = conn->tempaddr[0]->ai_next;
  }

  if(conn->tempsock[0] == CURL_SOCKET_BAD)
    return result;

  data->info.numconnects++; /* to track the number of connections made */

  return CURLE_OK;
}