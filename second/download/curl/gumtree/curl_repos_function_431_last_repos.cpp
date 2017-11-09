static int do_one_request(CURLM *m, char *URL, char *resolve)
{
  CURL *curls;
  struct curl_slist *resolve_list = NULL;
  int still_running;
  int res = 0;
  CURLMsg *msg;
  int msgs_left;

  resolve_list = curl_slist_append(resolve_list, resolve);

  easy_init(curls);

  easy_setopt(curls, CURLOPT_URL, URL);
  easy_setopt(curls, CURLOPT_RESOLVE, resolve_list);
  easy_setopt(curls, CURLOPT_DEBUGFUNCTION, debug_callback);
  easy_setopt(curls, CURLOPT_VERBOSE, 1);
  easy_setopt(curls, CURLOPT_DNS_CACHE_TIMEOUT, DNS_TIMEOUT);

  multi_add_handle(m, curls);
  multi_perform(m, &still_running);

  abort_on_test_timeout();

  while(still_running) {
    struct timeval timeout;
    fd_set fdread, fdwrite, fdexcep;
    int maxfd = -99;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    multi_fdset(m, &fdread, &fdwrite, &fdexcep, &maxfd);
    select_test(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

    abort_on_test_timeout();
    multi_perform(m, &still_running);

    abort_on_test_timeout();
  }

  do {
    msg = curl_multi_info_read(m, &msgs_left);
    if(msg && msg->msg == CURLMSG_DONE && msg->easy_handle == curls) {
      res = msg->data.result;
      break;
    }
  } while(msg);

test_cleanup:

  curl_multi_remove_handle(m, curls);
  curl_easy_cleanup(curls);
  curl_slist_free_all(resolve_list);

  return res;
}