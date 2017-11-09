void Curl_conncontrol(struct connectdata *conn,
                      int ctrl /* see defines in header */
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
                      , const char *reason
#endif
  )
{
  /* close if a connection, or a stream that isn't multiplexed */
  bool closeit = (ctrl == CONNCTRL_CONNECTION) ||
    ((ctrl == CONNCTRL_STREAM) && !(conn->handler->flags & PROTOPT_STREAM));
  if((ctrl == CONNCTRL_STREAM) &&
     (conn->handler->flags & PROTOPT_STREAM))
    DEBUGF(infof(conn->data, "Kill stream: %s\n", reason));
  else if(closeit != conn->bits.close) {
    DEBUGF(infof(conn->data, "Marked for [%s]: %s\n",
                 closeit?"closure":"keep alive", reason));
    conn->bits.close = closeit; /* the only place in the source code that
                                   should assign this bit */
  }
}