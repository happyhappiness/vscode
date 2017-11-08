static bool SocketIsDead(int sock)
{
  int sval;
  bool ret_val = TRUE;
  fd_set check_set;
  struct timeval to;

  FD_ZERO(&check_set);
  FD_SET(sock,&check_set);

  to.tv_sec = 0;
  to.tv_usec = 0;

  sval = select(sock + 1, &check_set, 0, 0, &to);
  if(sval == 0)
    /* timeout */
    ret_val = FALSE;

  return ret_val;
}