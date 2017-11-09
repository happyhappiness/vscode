bool Curl_connalive(struct connectdata *conn)
{
  /* First determine if ssl */
  if(conn->ssl[FIRSTSOCKET].use) {
    /* use the SSL context */
    if(!Curl_ssl_check_cxn(conn))
      return false;   /* FIN received */
  }
/* Minix 3.1 doesn't support any flags on recv; just assume socket is OK */
#ifdef MSG_PEEK
  else if(conn->sock[FIRSTSOCKET] == CURL_SOCKET_BAD)
    return false;
  else {
    /* use the socket */
    char buf;
    if(recv((RECV_TYPE_ARG1)conn->sock[FIRSTSOCKET], (RECV_TYPE_ARG2)&buf,
            (RECV_TYPE_ARG3)1, (RECV_TYPE_ARG4)MSG_PEEK) == 0) {
      return false;   /* FIN received */
    }
  }
#endif
  return true;
}