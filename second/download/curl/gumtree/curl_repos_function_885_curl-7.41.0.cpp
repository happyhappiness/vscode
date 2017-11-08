static CURLcode trynextip(struct connectdata *conn,
                          int sockindex,
                          int tempindex)
{
  const int other = tempindex ^ 1;
  CURLcode result = CURLE_COULDNT_CONNECT;

  /* First clean up after the failed socket.
     Don't close it yet to ensure that the next IP's socket gets a different
     file descriptor, which can prevent bugs when the curl_multi_socket_action
     interface is used with certain select() replacements such as kqueue. */
  curl_socket_t fd_to_close = conn->tempsock[tempindex];
  conn->tempsock[tempindex] = CURL_SOCKET_BAD;

  if(sockindex == FIRSTSOCKET) {
    Curl_addrinfo *ai = NULL;
    int family = AF_UNSPEC;

    if(conn->tempaddr[tempindex]) {
      /* find next address in the same protocol family */
      family = conn->tempaddr[tempindex]->ai_family;
      ai = conn->tempaddr[tempindex]->ai_next;
    }
    else if(conn->tempaddr[0]) {
      /* happy eyeballs - try the other protocol family */
      int firstfamily = conn->tempaddr[0]->ai_family;
#ifdef ENABLE_IPV6
      family = (firstfamily == AF_INET) ? AF_INET6 : AF_INET;
#else
      family = firstfamily;
#endif
      ai = conn->tempaddr[0]->ai_next;
    }

    while(ai) {
      if(conn->tempaddr[other]) {
        /* we can safely skip addresses of the other protocol family */
        while(ai && ai->ai_family != family)
          ai = ai->ai_next;
      }

      if(ai) {
        result = singleipconnect(conn, ai, &conn->tempsock[tempindex]);
        if(result == CURLE_COULDNT_CONNECT) {
          ai = ai->ai_next;
          continue;
        }

        conn->tempaddr[tempindex] = ai;
      }
      break;
    }
  }

  if(fd_to_close != CURL_SOCKET_BAD)
    Curl_closesocket(conn, fd_to_close);

  return result;
}