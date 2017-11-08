static gboolean timer_cb(gpointer data)
{
  GlobalInfo *g = (GlobalInfo *)data;
  CURLMcode rc;

  rc = curl_multi_socket_action(g->multi,
                                CURL_SOCKET_TIMEOUT, 0, &g->still_running);
  mcode_or_die("timer_cb: curl_multi_socket_action", rc);
  check_multi_info(g);
  return FALSE;
}