static int ctail_config_add_file (oconfig_item_t *ci)
{
  cu_tail_match_t *tm;
  cdtime_t interval = 0;
  char *plugin_instance = NULL;
  int num_matches = 0;
  int i;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("tail plugin: `File' needs exactly one string argument.");
    return (-1);
  }

  tm = tail_match_create (ci->values[0].value.string);
  if (tm == NULL)
  {
    ERROR ("tail plugin: tail_match_create (%s) failed.",
        ci->values[0].value.string);
    return (-1);
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;
    int status = 0;

    if (strcasecmp ("Instance", option->key) == 0)
      status = cf_util_get_string (option, &plugin_instance);
    else if (strcasecmp ("Interval", option->key) == 0)
      cf_util_get_cdtime (option, &interval);
    else if (strcasecmp ("Match", option->key) == 0)
    {
      status = ctail_config_add_match (tm, plugin_instance, option, interval);
      if (status == 0)
        num_matches++;
      /* Be mild with failed matches.. */
      status = 0;
    }
    else
    {
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  sfree (plugin_instance);

  if (num_matches == 0)
  {
    ERROR ("tail plugin: No (valid) matches found for file `%s'.",
        ci->values[0].value.string);
    tail_match_destroy (tm);
    return (-1);
  }
  else
  {
    cu_tail_match_t **temp;

    temp = (cu_tail_match_t **) realloc (tail_match_list,
        sizeof (cu_tail_match_t *) * (tail_match_list_num + 1));
    if (temp == NULL)
    {
      ERROR ("tail plugin: realloc failed.");
      tail_match_destroy (tm);
      return (-1);
    }

    tail_match_list = temp;
    tail_match_list[tail_match_list_num] = tm;
    tail_match_list_intervals[tail_match_list_num] = interval;
    tail_match_list_num++;
  }

  return (0);
}