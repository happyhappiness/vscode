static void setsock(SockInfo*f, curl_socket_t s, CURL*e, int act, GlobalInfo*g)
{
  printf("%s  \n", __PRETTY_FUNCTION__);

  int kind = (act&CURL_POLL_IN?EV_READ:0)|(act&CURL_POLL_OUT?EV_WRITE:0);

  f->sockfd = s;
  f->action = act;
  f->easy = e;
  if ( f->evset )
    ev_io_stop(g->loop, &f->ev);
  ev_io_init(&f->ev, event_cb, f->sockfd, kind);
  f->ev.data = g;
  f->evset=1;
  ev_io_start(g->loop, &f->ev);
}