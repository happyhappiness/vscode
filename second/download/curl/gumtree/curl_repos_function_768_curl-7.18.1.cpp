static int domore_getsock(struct connectdata *conn,
                          curl_socket_t *sock,
                          int numsocks)
{
  if(!numsocks)
    return GETSOCK_BLANK;

  /* When in DO_MORE state, we could be either waiting for us
     to connect to a remote site, or we could wait for that site
     to connect to us. It makes a difference in the way: if we
     connect to the site we wait for the socket to become writable, if
     the site connects to us we wait for it to become readable */
  sock[0] = conn->sock[SECONDARYSOCKET];

  return GETSOCK_WRITESOCK(0);
}