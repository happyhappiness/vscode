static int cc_config_add_match(web_page_t *page, /* {{{ */
                               oconfig_item_t *ci) {
  web_match_t *match;
  int status;

  if (ci->values_num != 0) {
    WARNING("curl plugin: Ignoring arguments for the `Match' block.");
  }

  match = calloc(1, sizeof(*match));
  if (match == NULL) {
    ERROR("curl plugin: calloc failed.");
    return (-1);
  }

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Regex", child->key) == 0)
      status = cf_util_get_string(child, &match->regex);
    else if (strcasecmp("ExcludeRegex", child->key) == 0)
      status = cf_util_get_string(child, &match->exclude_regex);
    else if (strcasecmp("DSType", child->key) == 0)
      status = cc_config_add_match_dstype(&match->dstype, child);
    else if (strcasecmp("Type", child->key) == 0)
      status = cf_util_get_string(child, &match->type);
    else if (strcasecmp("Instance", child->key) == 0)
      status = cf_util_get_string(child, &match->instance);
    else {
      WARNING("curl plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  while (status == 0) {
    if (match->regex == NULL) {
      WARNING("curl plugin: `Regex' missing in `Match' block.");
      status = -1;
    }

    if (match->type == NULL) {
      WARNING("curl plugin: `Type' missing in `Match' block.");
      status = -1;
    }

    if (match->dstype == 0) {
      WARNING("curl plugin: `DSType' missing in `Match' block.");
      status = -1;
    }

    break;
  } /* while (status == 0) */

  if (status != 0) {
    cc_web_match_free(match);
    return (status);
  }

  match->match =
      match_create_simple(match->regex, match->exclude_regex, match->dstype);
  if (match->match == NULL) {
    ERROR("curl plugin: match_create_simple failed.");
    cc_web_match_free(match);
    return (-1);
  } else {
    web_match_t *prev;

    prev = page->matches;
    while ((prev != NULL) && (prev->next != NULL))
      prev = prev->next;

    if (prev == NULL)
      page->matches = match;
    else
      prev->next = match;
  }

  return (0);
}