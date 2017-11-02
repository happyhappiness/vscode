static void setsock(SockInfo*f, curl_socket_t s, CURL*e, int act, GlobalInfo*g)
{
  GIOCondition kind =
     (act&CURL_POLL_IN?G_IO_IN:0)|(act&CURL_POLL_OUT?G_IO_OUT:0);

  f->sockfd = s;
  f->action = act;
  f->easy = e;
  if (f->ev) { g_source_remove(f->ev); }
  f->ev=g_io_add_watch(f->ch, kind, event_cb,g);

}