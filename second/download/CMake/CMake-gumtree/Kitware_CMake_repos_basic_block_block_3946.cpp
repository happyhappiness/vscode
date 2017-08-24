{
  struct events *ev = userp;
  struct socketmonitor *m;
  struct socketmonitor *prev=NULL;

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) easy;
#endif
  (void)socketp;

  m = ev->list;
  while(m) {
    if(m->socket.fd == s) {

      if(what == CURL_POLL_REMOVE) {
        struct socketmonitor *nxt = m->next;
        /* remove this node from the list of monitored sockets */
        if(prev)
          prev->next = nxt;
        else
          ev->list = nxt;
        free(m);
        m = nxt;
        infof(easy, "socket cb: socket %d REMOVED\n", s);
      }
      else {
        /* The socket 's' is already being monitored, update the activity
           mask. Convert from libcurl bitmask to the poll one. */
        m->socket.events = socketcb2poll(what);
        infof(easy, "socket cb: socket %d UPDATED as %s%s\n", s,
              what&CURL_POLL_IN?"IN":"",
              what&CURL_POLL_OUT?"OUT":"");
      }
      break;
    }
    prev = m;
    m = m->next; /* move to next node */
  }
  if(!m) {
    if(what == CURL_POLL_REMOVE) {
      /* this happens a bit too often, libcurl fix perhaps? */
      /* fprintf(stderr,
         "%s: socket %d asked to be REMOVED but not present!\n",
                 __func__, s); */
    }
    else {
      m = malloc(sizeof(struct socketmonitor));
      if(m) {
        m->next = ev->list;
        m->socket.fd = s;
        m->socket.events = socketcb2poll(what);
        m->socket.revents = 0;
        ev->list = m;
        infof(easy, "socket cb: socket %d ADDED as %s%s\n", s,
              what&CURL_POLL_IN?"IN":"",
              what&CURL_POLL_OUT?"OUT":"");
      }
      else
        return CURLE_OUT_OF_MEMORY;
    }
  }

  return 0;
}