static int cc_config_add_match (web_page_t *page, /* {{{ */
    oconfig_item_t *ci)
{
  web_match_t *match;
  int status;
  int i;

  if (ci->values_num != 0)
  {
    WARNING ("curl plugin: Ignoring arguments for the `Match' block.");
  }

  match = (web_match_t *) malloc (sizeof (*match));
  if (match == NULL)
  {
    ERROR ("curl plugin: malloc failed.");
    return (-1);
  }
  memset (match, 0, sizeof (*match));

  status = 0;
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Regex", child->key) == 0)
      status = cc_config_add_string ("Regex", &match->regex, child);
    else if (strcasecmp ("DSType", child->key) == 0)
      status = cc_config_add_match_dstype (&match->dstype, child);
    else if (strcasecmp ("Type", child->key) == 0)
      status = cc_config_add_string ("Type", &match->type, child);
    else if (strcasecmp ("Instance", child->key) == 0)
      status = cc_config_add_string ("Instance", &match->instance, child);
    else
    {
      WARNING ("curl plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  while (status == 0)
  {
    if (match->regex == NULL)
    {
      WARNING ("curl plugin: `Regex' missing in `Match' block.");
      status = -1;
    }

    if (match->type == NULL)
    {
      WARNING ("curl plugin: `Type' missing in `Match' block.");
      status = -1;
    }

    if (match->dstype == 0)
    {
      WARNING ("curl plugin: `DSType' missing in `Match' block.");
      status = -1;
    }

    break;
  } /* while (status == 0) */

  if (status != 0)
    return (status);

  match->match = match_create_simple (match->regex, match->dstype);
  if (match->match == NULL)
  {
    ERROR ("curl plugin: tail_match_add_match_simple failed.");
    cc_web_match_free (match);
    return (-1);
  }
  else
  {
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