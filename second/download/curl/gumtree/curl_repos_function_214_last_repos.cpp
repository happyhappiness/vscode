int main(int argc, char **argv)
{
  GlobalInfo g;
  (void)argc;
  (void)argv;

  memset(&g, 0, sizeof(GlobalInfo));
  g.evbase = event_base_new();
  init_fifo(&g);
  g.multi = curl_multi_init();
  g.timer_event = evtimer_new(g.evbase, timer_cb, &g);

  /* setup the generic multi interface options we want */
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETDATA, &g);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERDATA, &g);

  /* we don't call any curl_multi_socket*() function yet as we have no handles
     added! */

  event_base_dispatch(g.evbase);

  /* this, of course, won't get called since only way to stop this program is
     via ctrl-C, but it is here to show how cleanup /would/ be done. */
  clean_fifo(&g);
  event_free(g.timer_event);
  event_base_free(g.evbase);
  curl_multi_cleanup(g.multi);
  return 0;
}