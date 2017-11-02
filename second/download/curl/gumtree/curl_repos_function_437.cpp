int test(char *URL)
{
  int res = 0;
  CURLM *m = NULL;
  CURLMsg *msg; /* for picking up messages with the transfer status */
  int msgs_left; /* how many messages are left */
  int running;
  int handlenum = 0;
  struct timeval last_handle_add;

  if(parse_url_file("log/urls.txt") <= 0)
    goto test_cleanup;

  start_test_timing();

  curl_global_init(CURL_GLOBAL_ALL);

  multi_init(m);

  create_handles();

  multi_setopt(m, CURLMOPT_PIPELINING, 1L);
  multi_setopt(m, CURLMOPT_MAX_HOST_CONNECTIONS, 2L);
  multi_setopt(m, CURLMOPT_MAX_PIPELINE_LENGTH, 3L);
  multi_setopt(m, CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE, 15000L);
  multi_setopt(m, CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE, 10000L);

  multi_setopt(m, CURLMOPT_PIPELINING_SITE_BL, site_blacklist);
  multi_setopt(m, CURLMOPT_PIPELINING_SERVER_BL, server_blacklist);

  last_handle_add = tutil_tvnow();

  for(;;) {
    struct timeval interval;
    struct timeval now;
    long int msnow, mslast;
    fd_set rd, wr, exc;
    int maxfd = -99;
    long timeout;

    interval.tv_sec = 1;
    interval.tv_usec = 0;

    if(handlenum < num_handles) {
      now = tutil_tvnow();
      msnow = now.tv_sec * 1000 + now.tv_usec / 1000;
      mslast = last_handle_add.tv_sec * 1000 + last_handle_add.tv_usec / 1000;
      if((msnow - mslast) >= urltime[handlenum]) {
        fprintf(stdout, "Adding handle %d\n", handlenum);
        setup_handle(URL, m, handlenum);
        last_handle_add = now;
        handlenum++;
      }
    }

    curl_multi_perform(m, &running);

    abort_on_test_timeout();

    /* See how the transfers went */
    while ((msg = curl_multi_info_read(m, &msgs_left))) {
      if (msg->msg == CURLMSG_DONE) {
        int i, found = 0;

        /* Find out which handle this message is about */
        for (i = 0; i < num_handles; i++) {
          found = (msg->easy_handle == handles[i]);
          if(found)
            break;
        }

        printf("Handle %d Completed with status %d\n", i, msg->data.result);
        curl_multi_remove_handle(m, handles[i]);
      }
    }

    if(handlenum == num_handles && !running) {
      break; /* done */
    }

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&exc);

    curl_multi_fdset(m, &rd, &wr, &exc, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    curl_multi_timeout(m, &timeout);

    if(timeout < 0)
      timeout = 1;

    interval.tv_sec = timeout / 1000;
    interval.tv_usec = (timeout % 1000) * 1000;

    interval.tv_sec = 0;
    interval.tv_usec = 1000;

    select_test(maxfd+1, &rd, &wr, &exc, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

  remove_handles();

  /* undocumented cleanup sequence - type UB */

  curl_multi_cleanup(m);
  curl_global_cleanup();

  free_urls();
  return res;
}