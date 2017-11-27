static void cc_web_page_free (web_page_t *wp) /* {{{ */
{
  if (wp == NULL)
    return;

  if (wp->curl != NULL)
    curl_easy_cleanup (wp->curl);
  wp->curl = NULL;

  sfree (wp->instance);

  sfree (wp->url);
  sfree (wp->user);
  sfree (wp->pass);
  sfree (wp->credentials);
  sfree (wp->cacert);
  sfree (wp->post_body);
  curl_slist_free_all (wp->headers);
  curl_stats_destroy (wp->stats);

  sfree (wp->buffer);

  cc_web_match_free (wp->matches);
  cc_web_page_free (wp->next);
  sfree (wp);
}