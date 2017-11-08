static void new_conn(char *url, GlobalInfo *g )
{
  ConnInfo *conn;
  CURLMcode rc;

  conn = g_malloc0(sizeof(ConnInfo));

  conn->error[0]='\0';

  conn->easy = curl_easy_init();
  if (!conn->easy) {
    MSG_OUT("curl_easy_init() failed, exiting!\n");
    exit(2);
  }
  conn->global = g;
  conn->url = g_strdup(url);
  curl_easy_setopt(conn->easy, CURLOPT_URL, conn->url);
  curl_easy_setopt(conn->easy, CURLOPT_WRITEFUNCTION, write_cb);
  curl_easy_setopt(conn->easy, CURLOPT_WRITEDATA, &conn);
  curl_easy_setopt(conn->easy, CURLOPT_VERBOSE, SHOW_VERBOSE);
  curl_easy_setopt(conn->easy, CURLOPT_ERRORBUFFER, conn->error);
  curl_easy_setopt(conn->easy, CURLOPT_PRIVATE, conn);
  curl_easy_setopt(conn->easy, CURLOPT_NOPROGRESS, SHOW_PROGRESS?0:1);
  curl_easy_setopt(conn->easy, CURLOPT_PROGRESSFUNCTION, prog_cb);
  curl_easy_setopt(conn->easy, CURLOPT_PROGRESSDATA, conn);
  curl_easy_setopt(conn->easy, CURLOPT_FOLLOWLOCATION, 1);
  curl_easy_setopt(conn->easy, CURLOPT_CONNECTTIMEOUT, 30);
  curl_easy_setopt(conn->easy, CURLOPT_LOW_SPEED_LIMIT, 1);
  curl_easy_setopt(conn->easy, CURLOPT_LOW_SPEED_TIME, 30);

  MSG_OUT("Adding easy %p to multi %p (%s)\n", conn->easy, g->multi, url);
  rc =curl_multi_add_handle(g->multi, conn->easy);
  mcode_or_die("new_conn: curl_multi_add_handle", rc);
  g->requested++;
  do {
    rc = curl_multi_socket_all(g->multi, &g->still_running);
  } while (CURLM_CALL_MULTI_PERFORM == rc);
  mcode_or_die("new_conn: curl_multi_socket_all", rc);
  check_run_count(g);
}