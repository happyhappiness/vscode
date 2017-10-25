static bool trynextip(struct connectdata *conn,
                      int sockindex,
                      bool *connected)
{
  curl_socket_t sockfd;
  Curl_addrinfo *ai;

  if(sockindex != FIRSTSOCKET)
    return TRUE; /* no next */

  /* try the next address */
  ai = conn->ip_addr->ai_next;

  while (ai) {
    sockfd = singleipconnect(conn, ai, 0L, connected);
    if(sockfd != CURL_SOCKET_BAD) {
      /* store the new socket descriptor */
      conn->sock[sockindex] = sockfd;
      conn->ip_addr = ai;

      Curl_store_ip_addr(conn);
      return FALSE;
    }
    ai = ai->ai_next;
  }
  return TRUE;
}