int main(int argc, char **argv)
{
  GlobalInfo g;
  CURLMcode rc;

  memset(&g, 0, sizeof(GlobalInfo));
  event_init();
  init_fifo(&g);
  g.multi = curl_multi_init();
  evtimer_set(&g.timer_event, timer_cb, &g);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETDATA, &g);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERDATA, &g);
  do {
    rc = curl_multi_socket_all(g.multi, &g.still_running);
  } while (CURLM_CALL_MULTI_PERFORM == rc);
  event_dispatch();
  curl_multi_cleanup(g.multi);
  return 0;
}