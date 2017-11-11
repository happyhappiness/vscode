static void addsock(curl_socket_t s, CURL *easy, int action, GlobalInfo *g)
{
  SockInfo *fdp = g_malloc0(sizeof(SockInfo));

  fdp->global = g;
  fdp->ch=g_io_channel_unix_new(s);
  setsock(fdp, s, easy, action, g);
  curl_multi_assign(g->multi, s, fdp);
}