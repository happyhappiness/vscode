static void timer_cb(const boost::system::error_code & error, GlobalInfo *g)
{
  if(!error) {
    fprintf(MSG_OUT, "\ntimer_cb: ");

    CURLMcode rc;
    rc = curl_multi_socket_action(g->multi, CURL_SOCKET_TIMEOUT, 0,
                                  &g->still_running);

    mcode_or_die("timer_cb: curl_multi_socket_action", rc);
    check_multi_info(g);
  }
}