static int update_timeout_cb(CURLM *multi, long timeout_ms, void *userp)
{
  struct timeval timeout;
  GlobalInfo *g=(GlobalInfo *)userp;
  timeout.tv_sec = timeout_ms/1000;
  timeout.tv_usec = (timeout_ms%1000)*1000;

  MSG_OUT("*** update_timeout_cb %ld => %ld:%ld ***\n",
              timeout_ms, timeout.tv_sec, timeout.tv_usec);

  g->timer_event = g_timeout_add(timeout_ms, timer_cb, g);
  return 0;
}