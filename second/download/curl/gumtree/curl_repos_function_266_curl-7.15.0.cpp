static int data_pending(struct connectdata *conn)
{
  if(conn->ssl[FIRSTSOCKET].handle)
    /* SSL is in use */
    return SSL_pending(conn->ssl[FIRSTSOCKET].handle);

  return 0; /* nothing */
}