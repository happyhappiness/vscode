int raw_socket_poll (CONNECTION* conn, time_t wait_secs)
{
  fd_set rfds;
  unsigned long wait_millis, post_t_millis;
  struct timeval tv, pre_t, post_t;
  int rv;

  if (conn->fd < 0)
    return -1;

  wait_millis = wait_secs * 1000UL;

  FOREVER
  {
    tv.tv_sec = wait_millis / 1000;
    tv.tv_usec = (wait_millis % 1000) * 1000;

    FD_ZERO (&rfds);
    FD_SET (conn->fd, &rfds);

    gettimeofday (&pre_t, NULL);
    rv = select (conn->fd + 1, &rfds, NULL, NULL, &tv);
    gettimeofday (&post_t, NULL);

    if (rv > 0 ||
        (rv < 0 && errno != EINTR))
      return rv;

    if (SigInt)
      mutt_query_exit ();

    wait_millis += (pre_t.tv_sec * 1000UL) + (pre_t.tv_usec / 1000);
    post_t_millis = (post_t.tv_sec * 1000UL) + (post_t.tv_usec / 1000);
    if (wait_millis <= post_t_millis)
      return 0;
    wait_millis -= post_t_millis;
  }
}