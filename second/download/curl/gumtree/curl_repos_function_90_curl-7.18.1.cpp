static void timer_cb(int fd, short kind, void *userp)
{
  (void)fd;
  (void)kind;
  GlobalInfo *g = (GlobalInfo *)userp;
  CURLMcode rc;

  do {
    rc = curl_multi_socket(g->multi, CURL_SOCKET_TIMEOUT, &g->still_running);
  } while (rc == CURLM_CALL_MULTI_PERFORM);
  mcode_or_die("timer_cb: curl_multi_socket", rc);
  check_run_count(g);
}