static int cc_read_page (web_page_t *wp) /* {{{ */
{
  web_match_t *wm;
  int status;

  wp->buffer_fill = 0;
  status = curl_easy_perform (wp->curl);
  if (status != 0)
  {
    ERROR ("curl plugin: curl_easy_perform failed with staus %i: %s",
        status, wp->curl_errbuf);
    return (-1);
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