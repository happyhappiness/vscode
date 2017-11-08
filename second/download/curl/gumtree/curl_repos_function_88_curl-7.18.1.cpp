static void check_run_count(GlobalInfo *g)
{
  if (g->prev_running > g->still_running) {
    char *eff_url=NULL;
    CURLMsg *msg;
    int msgs_left;
    ConnInfo *conn=NULL;
    CURL*easy;
    CURLcode res;

    fprintf(MSG_OUT, "REMAINING: %d\n", g->still_running);
    /*
      I am still uncertain whether it is safe to remove an easy handle
      from inside the curl_multi_info_read loop, so here I will search
      for completed transfers in the inner "while" loop, and then remove
      them in the outer "do-while" loop...
   */
    do {
      easy=NULL;
      while ((msg = curl_multi_info_read(g->multi, &msgs_left))) {
        if (msg->msg == CURLMSG_DONE) {
          easy=msg->easy_handle;
          res=msg->data.result;
          break;
        }
      }
      if (easy) {
          curl_easy_getinfo(easy, CURLINFO_PRIVATE, &conn);
          curl_easy_getinfo(easy, CURLINFO_EFFECTIVE_URL, &eff_url);
          fprintf(MSG_OUT, "DONE: %s => (%d) %s\n", eff_url, res, conn->error);
          curl_multi_remove_handle(g->multi, easy);
          free(conn->url);
          curl_easy_cleanup(easy);
          free(conn);
      }
    } while ( easy );
  }
  g->prev_running = g->still_running;
}