curl_socket_t Curl_getconnectinfo(struct SessionHandle *data,
                                  struct connectdata **connp)
{
  curl_socket_t sockfd;

  DEBUGASSERT(data);

  /* this only works for an easy handle that has been used for
     curl_easy_perform()! */
  if(data->state.lastconnect && data->multi_easy) {
    struct connectdata *c = data->state.lastconnect;
    struct connfind find;
    find.tofind = data->state.lastconnect;
    find.found = FALSE;

    Curl_conncache_foreach(data->multi_easy->conn_cache, &find, conn_is_conn);

    if(!find.found) {
      data->state.lastconnect = NULL;
      return CURL_SOCKET_BAD;
    }

    if(connp)
      /* only store this if the caller cares for it */
      *connp = c;
    sockfd = c->sock[FIRSTSOCKET];
    /* we have a socket connected, let's determine if the server shut down */
    /* determine if ssl */
    if(c->ssl[FIRSTSOCKET].use) {
      /* use the SSL context */
      if(!Curl_ssl_check_cxn(c))
        return CURL_SOCKET_BAD;   /* FIN received */
    }
/* Minix 3.1 doesn't support any flags on recv; just assume socket is OK */
#ifdef MSG_PEEK
    else {
      /* use the socket */
      char buf;
      if(recv((RECV_TYPE_ARG1)c->sock[FIRSTSOCKET], (RECV_TYPE_ARG2)&buf,
              (RECV_TYPE_ARG3)1, (RECV_TYPE_ARG4)MSG_PEEK) == 0) {
        return CURL_SOCKET_BAD;   /* FIN received */
      }
    }
#endif
  }
  else
    return CURL_SOCKET_BAD;

  return sockfd;
}