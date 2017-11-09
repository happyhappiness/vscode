static void setsock(SockInfo *f, curl_socket_t s, CURL *e, int act,
                    GlobalInfo *g)
{
  int kind =
     (act&CURL_POLL_IN?EV_READ:0)|(act&CURL_POLL_OUT?EV_WRITE:0)|EV_PERSIST;

  f->sockfd = s;
  f->action = act;
  f->easy = e;
  if(f->evset)
    event_free(f->ev);
  f->ev = event_new(g->evbase, f->sockfd, kind, event_cb, g);
  f->evset = 1;
  event_add(f->ev, NULL);
}