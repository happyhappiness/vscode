static int cc_read_page (web_page_t *wp) /* {{{ */
{
  web_match_t *wm;
  int status;
  struct timeval start, end;

  if (wp->response_time)
    gettimeofday (&start, NULL);

  wp->buffer_fill = 0;
  status = curl_easy_perform (wp->curl);
  if (status != 0)
  {
    ERROR ("curl plugin: curl_easy_perform failed with staus %i: %s",
        status, wp->curl_errbuf);
    return (-1);
  }

  if (wp->response_time)
  {
    double secs = 0;
    gettimeofday (&end, NULL);
    secs += end.tv_sec - start.tv_sec;
    secs += (end.tv_usec - start.tv_usec) / 1000000.0;
    cc_submit_response_time (wp, secs);
  }

  for (wm = wp->matches; wm != NULL; wm = wm->next)
  {
    cu_match_value_t *mv;

    status = match_apply (wm->match, wp->buffer);
    if (status != 0)
    {
      WARNING ("curl plugin: match_apply failed.");
      continue;
    }

    mv = match_get_user_data (wm->match);
    if (mv == NULL)
    {
      WARNING ("curl plugin: match_get_user_data returned NULL.");
      continue;
    }

    cc_submit (wp, wm, mv);
  } /* for (wm = wp->matches; wm != NULL; wm = wm->next) */

  return (0);
}