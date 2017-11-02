static int multi_timer_cb(CURLM *multi, long timeout_ms, GlobalInfo *g)
{
  DPRINT("%s %li\n", __PRETTY_FUNCTION__,  timeout_ms);
  ev_timer_stop(g->loop, &g->timer_event);
  if (timeout_ms > 0)
  {
    double  t = timeout_ms / 1000;
    ev_timer_init(&g->timer_event, timer_cb, t, 0.);
    ev_timer_start(g->loop, &g->timer_event);
  }else
    timer_cb(g->loop, &g->timer_event, 0);
  return 0;
}