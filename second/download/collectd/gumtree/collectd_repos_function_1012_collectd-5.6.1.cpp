static int cc_config_add_page (oconfig_item_t *ci) /* {{{ */
{
  web_page_t *page;
  int status;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("curl plugin: `Page' blocks need exactly one string argument.");
    return (-1);
  }

  page = calloc (1, sizeof (*page));
  if (page == NULL)
  {
    ERROR ("curl plugin: calloc failed.");
    return (-1);
  }
  page->url = NULL;
  page->user = NULL;
  page->pass = NULL;
  page->digest = 0;
  page->verify_peer = 1;
  page->verify_host = 1;
  page->response_time = 0;
  page->response_code = 0;
  page->timeout = -1;
  page->stats = NULL;

  page->instance = strdup (ci->values[0].value.string);
  if (page->instance == NULL)
  {
    ERROR ("curl plugin: strdup failed.");
    sfree (page);
    return (-1);
  }

  /* Process all children */
  status = 0;
  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("URL", child->key) == 0)
      status = cf_util_get_string (child, &page->url);
    else if (strcasecmp ("User", child->key) == 0)
      status = cf_util_get_string (child, &page->user);
    else if (strcasecmp ("Password", child->key) == 0)
      status = cf_util_get_string (child, &page->pass);
    else if (strcasecmp ("Digest", child->key) == 0)
      status = cf_util_get_boolean (child, &page->digest);
    else if (strcasecmp ("VerifyPeer", child->key) == 0)
      status = cf_util_get_boolean (child, &page->verify_peer);
    else if (strcasecmp ("VerifyHost", child->key) == 0)
      status = cf_util_get_boolean (child, &page->verify_host);
    else if (strcasecmp ("MeasureResponseTime", child->key) == 0)
      status = cf_util_get_boolean (child, &page->response_time);
    else if (strcasecmp ("MeasureResponseCode", child->key) == 0)
      status = cf_util_get_boolean (child, &page->response_code);
    else if (strcasecmp ("CACert", child->key) == 0)
      status = cf_util_get_string (child, &page->cacert);
    else if (strcasecmp ("Match", child->key) == 0)
      /* Be liberal with failing matches => don't set `status'. */
      cc_config_add_match (page, child);
    else if (strcasecmp ("Header", child->key) == 0)
      status = cc_config_append_string ("Header", &page->headers, child);
    else if (strcasecmp ("Post", child->key) == 0)
      status = cf_util_get_string (child, &page->post_body);
    else if (strcasecmp ("Timeout", child->key) == 0)
      status = cf_util_get_int (child, &page->timeout);
    else if (strcasecmp ("Statistics", child->key) == 0) {
      page->stats = curl_stats_from_config (child);
      if (page->stats == NULL)
        status = -1;
    }
    else
    {
      WARNING ("curl plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  /* Additionial sanity checks and libCURL initialization. */
  while (status == 0)
  {
    if (page->url == NULL)
    {
      WARNING ("curl plugin: `URL' missing in `Page' block.");
      status = -1;
    }

    if (page->matches == NULL && page->stats == NULL
        && !page->response_time && !page->response_code)
    {
      assert (page->instance != NULL);
      WARNING ("curl plugin: No (valid) `Match' block "
          "or Statistics or MeasureResponseTime or MeasureResponseCode "
          "within `Page' block `%s'.", page->instance);
      status = -1;
    }

    if (status == 0)
      status = cc_page_init_curl (page);

    break;
  } /* while (status == 0) */

  if (status != 0)
  {
    cc_web_page_free (page);
    return (status);
  }

  /* Add the new page to the linked list */
  if (pages_g == NULL)
    pages_g = page;
  else
  {
    web_page_t *prev;

    prev = pages_g;
    while (prev->next != NULL)
      prev = prev->next;
    prev->next = page;
  }

  return (0);
}