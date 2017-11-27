static int gmond_config_add_metric (oconfig_item_t *ci) /* {{{ */
{
  metric_map_t *map;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("gmond plugin: `Metric' blocks need "
        "exactly one string argument.");
    return (-1);
  }

  map = realloc (metric_map, (metric_map_len + 1) * sizeof (*metric_map));
  if (map == NULL)
  {
    ERROR ("gmond plugin: realloc failed.");
    return (-1);
  }
  metric_map = map;
  map = metric_map + metric_map_len;

  memset (map, 0, sizeof (*map));
  map->type = NULL;
  map->type_instance = NULL;
  map->ds_name = NULL;
  map->ds_type = -1;
  map->ds_index = -1;

  map->ganglia_name = strdup (ci->values[0].value.string);
  if (map->ganglia_name == NULL)
  {
    ERROR ("gmond plugin: strdup failed.");
    return (-1);
  }

  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp ("Type", child->key) == 0)
      gmond_config_set_string (child, &map->type);
    else if (strcasecmp ("TypeInstance", child->key) == 0)
      gmond_config_set_string (child, &map->type_instance);
    else if (strcasecmp ("DataSource", child->key) == 0)
      gmond_config_set_string (child, &map->ds_name);
    else
    {
      WARNING ("gmond plugin: Unknown configuration option `%s' ignored.",
          child->key);
    }
  }

  if (map->type == NULL)
  {
    ERROR ("gmond plugin: No type is set for metric %s.",
        map->ganglia_name);
    sfree (map->ganglia_name);
    sfree (map->type_instance);
    return (-1);
  }

  metric_map_len++;
  return (0);
}