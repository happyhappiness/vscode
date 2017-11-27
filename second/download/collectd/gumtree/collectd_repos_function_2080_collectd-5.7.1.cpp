static int cmc_config_add_page(oconfig_item_t *ci) /* {{{ */
{
  web_page_t *page;
  int status;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING(
        "memcachec plugin: `Page' blocks need exactly one string argument.");
    return (-1);
  }

  page = calloc(1, sizeof(*page));
  if (page == NULL) {
    ERROR("memcachec plugin: calloc failed.");
    return (-1);
  }
  page->server = NULL;
  page->key = NULL;

  page->instance = strdup(ci->values[0].value.string);
  if (page->instance == NULL) {
    ERROR("memcachec plugin: strdup failed.");
    sfree(page);
    return (-1);
  }

  /* Process all children */
  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Server", child->key) == 0)
      status = cmc_config_add_string("Server", &page->server, child);
    else if (strcasecmp("Key", child->key) == 0)
      status = cmc_config_add_string("Key", &page->key, child);
    else if (strcasecmp("Match", child->key) == 0)
      /* Be liberal with failing matches => don't set `status'. */
      cmc_config_add_match(page, child);
    else {
      WARNING("memcachec plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  /* Additionial sanity checks and libmemcached initialization. */
  while (status == 0) {
    if (page->server == NULL) {
      WARNING("memcachec plugin: `Server' missing in `Page' block.");
      status = -1;
    }

    if (page->key == NULL) {
      WARNING("memcachec plugin: `Key' missing in `Page' block.");
      status = -1;
    }

    if (page->matches == NULL) {
      assert(page->instance != NULL);
      WARNING("memcachec plugin: No (valid) `Match' block "
              "within `Page' block `%s'.",
              page->instance);
      status = -1;
    }

    if (status == 0)
      status = cmc_page_init_memc(page);

    break;
  } /* while (status == 0) */

  if (status != 0) {
    cmc_web_page_free(page);
    return (status);
  }

  /* Add the new page to the linked list */
  if (pages_g == NULL)
    pages_g = page;
  else {
    web_page_t *prev;

    prev = pages_g;
    while (prev->next != NULL)
      prev = prev->next;
    prev->next = page;
  }

  return (0);
}