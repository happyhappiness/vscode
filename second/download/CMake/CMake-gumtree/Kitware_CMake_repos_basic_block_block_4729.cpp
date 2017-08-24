{
  int i;
  int s=0;
  int rc=0;

  if(!numsocks)
    return GETSOCK_BLANK;

#ifdef USE_SSL
  if(CONNECT_FIRSTSOCKET_PROXY_SSL())
    return Curl_ssl_getsock(conn, sock, numsocks);
#endif

  for(i=0; i<2; i++) {
    if(conn->tempsock[i] != CURL_SOCKET_BAD) {
      sock[s] = conn->tempsock[i];
      rc |= GETSOCK_WRITESOCK(s++);
    }
  }

  return rc;
}