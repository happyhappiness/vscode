static void cmc_web_page_free(web_page_t *wp) /* {{{ */
{
  if (wp == NULL)
    return;

  if (wp->memc != NULL)
    memcached_free(wp->memc);
  wp->memc = NULL;

  sfree(wp->instance);
  sfree(wp->server);
  sfree(wp->key);
  sfree(wp->buffer);

  cmc_web_match_free(wp->matches);
  cmc_web_page_free(wp->next);
  sfree(wp);
}