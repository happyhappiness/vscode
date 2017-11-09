int main(int argc, char **argv)
{
  GlobalInfo g;
  CURLMcode rc;
  (void)argc;
  (void)argv;

  memset(&g, 0, sizeof(GlobalInfo));
  g.loop = ev_default_loop(0);

  init_fifo(&g);
  g.multi = curl_multi_init();

  ev_timer_init(&g.timer_event, timer_cb, 0., 0.);
  g.timer_event.data = &g;
  g.fifo_event.data = &g;
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETDATA, &g);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERDATA, &g);

  /* we don't call any curl_multi_socket*() function yet as we have no handles
     added! */

  ev_loop(g.loop, 0);
  curl_multi_cleanup(g.multi);
  return 0;
}