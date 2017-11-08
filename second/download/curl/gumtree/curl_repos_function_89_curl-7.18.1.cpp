static void event_cb(int fd, short kind, void *userp)
{
  GlobalInfo *g = (GlobalInfo*) userp;
  CURLMcode rc;

  do {
    rc = curl_multi_socket(g->multi, fd, &g->still_running);
  } while (rc == CURLM_CALL_MULTI_PERFORM);
  mcode_or_die("event_cb: curl_multi_socket", rc);
  check_run_count(g);
  if ( g->still_running <= 0 ) {
    fprintf(MSG_OUT, "last transfer done, kill timeout\n");
    if (evtimer_pending(&g->timer_event, NULL)) {
      evtimer_del(&g->timer_event);
    }
  }
}