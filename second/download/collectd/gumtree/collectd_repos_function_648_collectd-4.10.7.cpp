static int bind_config_add_view (oconfig_item_t *ci) /* {{{ */
{
  cb_view_t *tmp;
  int i;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("bind plugin: `View' blocks need exactly one string argument.");
    return (-1);
  }

  tmp = (cb_view_t *) realloc (views, sizeof (*views) * (views_num + 1));
  if (tmp == NULL)
  {
    ERROR ("bind plugin: realloc failed.");
    return (-1);
  }
  views = tmp;
  tmp = views + views_num;

  memset (tmp, 0, sizeof (*tmp));
  tmp->qtypes = 1;
  tmp->resolver_stats = 1;
  tmp->cacherrsets = 1;
  tmp->zones = NULL;
  tmp->zones_num = 0;

  tmp->name = strdup (ci->values[0].value.string);
  if (tmp->name == NULL)
  {
    ERROR ("bind plugin: strdup failed.");
    free (tmp);
    return (-1);
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("QTypes", child->key) == 0)
      bind_config_set_bool ("QTypes", &tmp->qtypes, child);
    else if (strcasecmp ("ResolverStats", child->key) == 0)
      bind_config_set_bool ("ResolverStats", &tmp->resolver_stats, child);
    else if (strcasecmp ("CacheRRSets", child->key) == 0)
      bind_config_set_bool ("CacheRRSets", &tmp->cacherrsets, child);
    else if (strcasecmp ("Zone", child->key) == 0)
      bind_config_add_view_zone (tmp, child);
    else
    {
      WARNING ("bind plugin: Unknown configuration option "
          "`%s' in view `%s' will be ignored.", child->key, tmp->name);
    }
  } /* for (i = 0; i < ci->children_num; i++) */

  views_num++;
  return (0);
}