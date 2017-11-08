static int ssh_perform_getsock(const struct connectdata *conn,
                               curl_socket_t *sock, /* points to numsocks
                                                       number of sockets */
                               int numsocks)
{
#ifdef HAVE_LIBSSH2_SESSION_BLOCK_DIRECTION
  int bitmap = GETSOCK_BLANK;
  (void)numsocks;

  sock[0] = conn->sock[FIRSTSOCKET];

  if(conn->waitfor & KEEP_RECV)
    bitmap |= GETSOCK_READSOCK(FIRSTSOCKET);

  if(conn->waitfor & KEEP_SEND)
    bitmap |= GETSOCK_WRITESOCK(FIRSTSOCKET);

  return bitmap;
#else
  /* if we don't know the direction we can use the generic *_getsock()
     function even for the protocol_connect and doing states */
  return Curl_single_getsock(conn, sock, numsocks);
#endif
}