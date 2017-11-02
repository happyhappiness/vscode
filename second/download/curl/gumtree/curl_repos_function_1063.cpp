static int ssh_getsock(struct connectdata *conn,
                       curl_socket_t *sock, /* points to numsocks number
                                               of sockets */
                       int numsocks)
{
#ifndef HAVE_LIBSSH2_SESSION_BLOCK_DIRECTION
  (void)conn;
  (void)sock;
  (void)numsocks;
  /* if we don't know any direction we can just play along as we used to and
     not provide any sensible info */
  return GETSOCK_BLANK;
#else
  /* if we know the direction we can use the generic *_getsock() function even
     for the protocol_connect and doing states */
  return ssh_perform_getsock(conn, sock, numsocks);
#endif
}