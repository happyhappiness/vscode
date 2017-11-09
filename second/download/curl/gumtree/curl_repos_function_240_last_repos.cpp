static void new_conn(char *url, GlobalInfo *g)
{
  ConnInfo *conn;
  CURLMcode rc;

  conn = (ConnInfo *) calloc(1, sizeof(ConnInfo));

  conn->easy = curl_easy_init();
  if(!conn->easy) {
    fprintf(MSG_OUT, "\ncurl_easy_init() failed, exiting!");
    exit(2);
  }

  conn->global = g;
  conn->url = strdup(url);
  curl_easy_setopt(conn->easy, CURLOPT_URL, conn->url);
  curl_easy_setopt(conn->easy, CURLOPT_WRITEFUNCTION, write_cb);
  curl_easy_setopt(conn->easy, CURLOPT_WRITEDATA, &conn);
  curl_easy_setopt(conn->easy, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(conn->easy, CURLOPT_ERRORBUFFER, conn->error);
  curl_easy_setopt(conn->easy, CURLOPT_PRIVATE, conn);
  curl_easy_setopt(conn->easy, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(conn->easy, CURLOPT_PROGRESSFUNCTION, prog_cb);
  curl_easy_setopt(conn->easy, CURLOPT_PROGRESSDATA, conn);
  curl_easy_setopt(conn->easy, CURLOPT_LOW_SPEED_TIME, 3L);
  curl_easy_setopt(conn->easy, CURLOPT_LOW_SPEED_LIMIT, 10L);

  /* call this function to get a socket */
  curl_easy_setopt(conn->easy, CURLOPT_OPENSOCKETFUNCTION, opensocket);

  /* call this function to close a socket */
  curl_easy_setopt(conn->easy, CURLOPT_CLOSESOCKETFUNCTION, close_socket);

  fprintf(MSG_OUT,
          "\nAdding easy %p to multi %p (%s)", conn->easy, g->multi, url);
  rc = curl_multi_add_handle(g->multi, conn->easy);
  mcode_or_die("new_conn: curl_multi_add_handle", rc);

  /* note that the add_handle() will set a time-out to trigger very soon so
     that the necessary socket_action() call will be called by this app */
}