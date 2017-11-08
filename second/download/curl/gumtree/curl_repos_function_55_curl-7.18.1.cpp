static gboolean timer_cb(gpointer data)
{
  GlobalInfo *g = (GlobalInfo *)data;
  CURLMcode rc;

  do {
    rc = curl_multi_socket(g->multi, CURL_SOCKET_TIMEOUT, &g->still_running);
  } while (rc == CURLM_CALL_MULTI_PERFORM);
  mcode_or_die("timer_cb: curl_multi_socket", rc);
  check_run_count(g);
  return FALSE;
}