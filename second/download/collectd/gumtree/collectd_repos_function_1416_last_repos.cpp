static metric_map_t *metric_lookup(const char *key) /* {{{ */
{
  metric_map_t *map;
  size_t map_len;
  size_t i;

  /* Search the user-supplied table first.. */
  map = metric_map;
  map_len = metric_map_len;
  for (i = 0; i < map_len; i++)
    if (strcmp(map[i].ganglia_name, key) == 0)
      break;

  /* .. and fall back to the built-in table if nothing is found. */
  if (i >= map_len) {
    map = metric_map_default;
    map_len = metric_map_len_default;

    for (i = 0; i < map_len; i++)
      if (strcmp(map[i].ganglia_name, key) == 0)
        break;
  }

  if (i >= map_len)
    return NULL;

  /* Look up the DS type and ds_index. */
  if (map[i].ds_type < 0) /* {{{ */
  {
    const data_set_t *ds;

    ds = plugin_get_ds(map[i].type);
    if (ds == NULL) {
      WARNING("gmond plugin: Type not defined: %s", map[i].type);
      return NULL;
    }

    if ((map[i].ds_name == NULL) && (ds->ds_num != 1)) {
      WARNING("gmond plugin: No data source name defined for metric %s, "
              "but type %s has more than one data source.",
              map[i].ganglia_name, map[i].type);
      return NULL;
    }

    if (map[i].ds_name == NULL) {
      map[i].ds_index = 0;
    } else {
      size_t j;

      for (j = 0; j < ds->ds_num; j++)
        if (strcasecmp(ds->ds[j].name, map[i].ds_name) == 0)
          break;

      if (j >= ds->ds_num) {
        WARNING("gmond plugin: There is no data source "
                "named `%s' in type `%s'.",
                map[i].ds_name, ds->type);
        return NULL;
      }
      map[i].ds_index = j;
    }

    map[i].ds_type = ds->ds[map[i].ds_index].type;
  } /* }}} if ((map[i].ds_type < 0) || (map[i].ds_index < 0)) */

  return map + i;
}