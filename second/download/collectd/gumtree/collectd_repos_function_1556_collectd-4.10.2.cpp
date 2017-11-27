static int ctail_config_add_match (cu_tail_match_t *tm,
    const char *plugin_instance, oconfig_item_t *ci)
{
  ctail_config_match_t cm;
  int status;
  int i;

  memset (&cm, '\0', sizeof (cm));

  if (ci->values_num != 0)
  {
    WARNING ("tail plugin: Ignoring arguments for the `Match' block.");
  }

  status = 0;
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Regex", option->key) == 0)
      status = ctail_config_add_string ("Regex", &cm.regex, option);
    else if (strcasecmp ("ExcludeRegex", option->key) == 0)
      status = ctail_config_add_string ("ExcludeRegex", &cm.excluderegex,
					option);
    else if (strcasecmp ("DSType", option->key) == 0)
      status = ctail_config_add_match_dstype (&cm, option);
    else if (strcasecmp ("Type", option->key) == 0)
      status = ctail_config_add_string ("Type", &cm.type, option);
    else if (strcasecmp ("Instance", option->key) == 0)
      status = ctail_config_add_string ("Instance", &cm.type_instance, option);
    else
    {
      WARNING ("tail plugin: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  while (status == 0)
  {
    if (cm.regex == NULL)
    {
      WARNING ("tail plugin: `Regex' missing in `Match' block.");
      status = -1;
      break;
    }

    if (cm.type == NULL)
    {
      WARNING ("tail plugin: `Type' missing in `Match' block.");
      status = -1;
      break;
    }

    if (cm.flags == 0)
    {
      WARNING ("tail plugin: `DSType' missing in `Match' block.");
      status = -1;
      break;
    }

    break;
  } /* while (status == 0) */

  if (status == 0)
  {
    status = tail_match_add_match_simple (tm, cm.regex, cm.excluderegex,
	cm.flags, "tail", plugin_instance, cm.type, cm.type_instance);

    if (status != 0)
    {
      ERROR ("tail plugin: tail_match_add_match_simple failed.");
    }
  }

  sfree (cm.regex);
  sfree (cm.excluderegex);
  sfree (cm.type);
  sfree (cm.type_instance);

  return (status);
}