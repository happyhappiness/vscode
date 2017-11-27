static int cc_config_add_page (oconfig_item_t *ci) /* {{{ */
{
  web_page_t *page;
  int status;
  int i;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("curl plugin: `Page' blocks need exactly one string argument.");
    return (-1);
  }

  page = (web_page_t *) malloc (sizeof (*page));
  if (page == NULL)
  {
    ERROR ("curl plugin: malloc failed.");
    return (-1);
  }
  memset (page, 0, sizeof (*page));
  page->url = NULL;
  page->user = NULL;
  page->pass = NULL;
  page->verify_peer = 1;
  page->verify_host = 1;
  page->response_time = 0;

  page->instance = strdup (ci->values[0].value.string);
  if (page->instance == NULL)
  {
    ERROR ("curl plugin: strdup failed.");
    sfree (page);
    return (-1);
  }

  /* Process all children */
  status = 0;
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("URL", child->key) == 0)
      status = cc_config_add_string ("URL", &page->url, child);
    else if (strcasecmp ("User", child->key) == 0)
      status = cc_config_add_string ("User", &page->user, child);
    else if (strcasecmp ("Password", child->key) == 0)
      status = cc_config_add_string ("Password", &page->pass, child);
    else if (strcasecmp ("VerifyPeer", child->key) == 0)
      status = cc_config_set_boolean ("VerifyPeer", &page->verify_peer, child);
    else if (strcasecmp ("VerifyHost", child->key) == 0)
      status = cc_config_set_boolean ("VerifyHost", &page->verify_host, child);
    else if (strcasecmp ("MeasureResponseTime", child->key) == 0)
      status = cc_config_set_boolean (child->key, &page->response_time, child);
    else if (strcasecmp ("CACert", child->key) == 0)
      status = cc_config_add_string ("CACert", &page->cacert, child);
    else if (strcasecmp ("Match", child->key) == 0)
      /* Be liberal with failing matches => don't set `status'. */
      cc_config_add_match (page, child);
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

    if (page->matches == NULL && !page->response_time)
    {
      assert (page->instance != NULL);
      WARNING ("curl plugin: No (valid) `Match' block "
          "or MeasureResponseTime within `Page' block `%s'.", page->instance);
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
    while ((prev != NULL) && (prev->next != NULL))
      prev = prev->next;
    prev->next = page;
  }

  return (0);
}