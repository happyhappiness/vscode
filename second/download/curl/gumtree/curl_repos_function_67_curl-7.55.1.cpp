static void event_cb(EV_P_ struct ev_io *w, int revents)
{
  DPRINT("%s  w %p revents %i\n", __PRETTY_FUNCTION__, w, revents);
  GlobalInfo *g = (GlobalInfo*) w->data;
  CURLMcode rc;

  int action = (revents&EV_READ?CURL_POLL_IN:0)|
    (revents&EV_WRITE?CURL_POLL_OUT:0);
  rc = curl_multi_socket_action(g->multi, w->fd, action, &g->still_running);
  mcode_or_die("event_cb: curl_multi_socket_action", rc);
  check_multi_info(g);
  if(g->still_running <= 0) {
    fprintf(MSG_OUT, "last transfer done, kill timeout\n");
    ev_timer_stop(g->loop, &g->timer_event);
  }
}