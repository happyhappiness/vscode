static void timer_cb(EV_P_ struct ev_timer *w, int revents)
{
  DPRINT("%s  w %p revents %i\n", __PRETTY_FUNCTION__, w, revents);

  GlobalInfo *g = (GlobalInfo *)w->data;
  CURLMcode rc;

  rc = curl_multi_socket_action(g->multi, CURL_SOCKET_TIMEOUT, 0, &g->still_running);
  mcode_or_die("timer_cb: curl_multi_socket_action", rc);
  check_multi_info(g);
}