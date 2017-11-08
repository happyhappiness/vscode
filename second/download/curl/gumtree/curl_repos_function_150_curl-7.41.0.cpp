static gboolean event_cb(GIOChannel *ch, GIOCondition condition, gpointer data)
{
  GlobalInfo *g = (GlobalInfo*) data;
  CURLMcode rc;
  int fd=g_io_channel_unix_get_fd(ch);

  int action =
    (condition & G_IO_IN ? CURL_CSELECT_IN : 0) |
    (condition & G_IO_OUT ? CURL_CSELECT_OUT : 0);

  rc = curl_multi_socket_action(g->multi, fd, action, &g->still_running);
  mcode_or_die("event_cb: curl_multi_socket_action", rc);

  check_multi_info(g);
  if(g->still_running) {
    return TRUE;
  } else {
    MSG_OUT("last transfer done, kill timeout\n");
    if (g->timer_event) { g_source_remove(g->timer_event); }
    return FALSE;
  }
}