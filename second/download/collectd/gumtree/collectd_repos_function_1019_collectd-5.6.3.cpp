static int cc_read_page(web_page_t *wp) /* {{{ */
{
  int status;
  cdtime_t start = 0;

  if (wp->response_time)
    start = cdtime();

  wp->buffer_fill = 0;

  curl_easy_setopt(wp->curl, CURLOPT_URL, wp->url);

  status = curl_easy_perform(wp->curl);
  if (status != CURLE_OK) {
    ERROR("curl plugin: curl_easy_perform failed with status %i: %s", status,
          wp->curl_errbuf);
    return (-1);
  }

  if (wp->response_time)
    cc_submit_response_time(wp, cdtime() - start);
  if (wp->stats != NULL)
    curl_stats_dispatch(wp->stats, wp->curl, hostname_g, "curl", wp->instance);

  if (wp->response_code) {
    long response_code = 0;
    status =
        curl_easy_getinfo(wp->curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (status != CURLE_OK) {
      ERROR("curl plugin: Fetching response code failed with status %i: %s",
            status, wp->curl_errbuf);
    } else {
      cc_submit_response_code(wp, response_code);
    }
  }

  for (web_match_t *wm = wp->matches; wm != NULL; wm = wm->next) {
    cu_match_value_t *mv;

    status = match_apply(wm->match, wp->buffer);
    if (status != 0) {
      WARNING("curl plugin: match_apply failed.");
      continue;
    }

    mv = match_get_user_data(wm->match);
    if (mv == NULL) {
      WARNING("curl plugin: match_get_user_data returned NULL.");
      continue;
    }

    cc_submit(wp, wm, mv);
    match_value_reset(mv);
  } /* for (wm = wp->matches; wm != NULL; wm = wm->next) */

  return (0);
}