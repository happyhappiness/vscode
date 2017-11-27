static int cmc_read_page (web_page_t *wp) /* {{{ */
{
  web_match_t *wm;
  memcached_return rc;
  size_t string_length;
  uint32_t flags;
  int status;

  if (wp->memc == NULL)
    return (-1);

  wp->buffer = memcached_get (wp->memc, wp->key, strlen (wp->key),
                              &string_length, &flags, &rc);
  if (rc != MEMCACHED_SUCCESS)
  {
    ERROR ("memcachec plugin: memcached_get failed: %s",
        memcached_strerror (wp->memc, rc));
    return (-1);
  }

  for (wm = wp->matches; wm != NULL; wm = wm->next)
  {
    cu_match_value_t *mv;

    status = match_apply (wm->match, wp->buffer);
    if (status != 0)
    {
      WARNING ("memcachec plugin: match_apply failed.");
      continue;
    }

    mv = match_get_user_data (wm->match);
    if (mv == NULL)
    {
      WARNING ("memcachec plugin: match_get_user_data returned NULL.");
      continue;
    }

    cmc_submit (wp, wm, mv);
  } /* for (wm = wp->matches; wm != NULL; wm = wm->next) */

  sfree (wp->buffer);

  return (0);
}