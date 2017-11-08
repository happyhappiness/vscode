static gboolean event_cb(GIOChannel *ch, GIOCondition condition, gpointer data)
{
  GlobalInfo *g = (GlobalInfo*) data;
  CURLMcode rc;
  int fd=g_io_channel_unix_get_fd(ch);
  do {
    rc = curl_multi_socket(g->multi, fd, &g->still_running);
  } while (rc == CURLM_CALL_MULTI_PERFORM);
  mcode_or_die("event_cb: curl_multi_socket", rc);
  check_run_count(g);
  if(g->still_running) {
    return TRUE;
  } else {
    MSG_OUT("last transfer done, kill timeout\n");
    if (g->timer_event) { g_source_remove(g->timer_event); }
    return FALSE;
  }
}