static int ethstat_add_map (const oconfig_item_t *ci) /* {{{ */
{
  value_map_t *map;
  int status;
  char *key;

  if ((ci->values_num < 2)
      || (ci->values_num > 3)
      || (ci->values[0].type != OCONFIG_TYPE_STRING)
      || (ci->values[1].type != OCONFIG_TYPE_STRING)
      || ((ci->values_num == 3)
        && (ci->values[2].type != OCONFIG_TYPE_STRING)))
  {
    ERROR ("ethstat plugin: The %s option requires "
        "two or three string arguments.", ci->key);
    return (-1);
  }

  key = strdup (ci->values[0].value.string);
  if (key == NULL)
  {
    ERROR ("ethstat plugin: strdup(3) failed.");
    return (ENOMEM);
  }

  map = malloc (sizeof (*map));
  if (map == NULL)
  {
    sfree (key);
    ERROR ("ethstat plugin: malloc(3) failed.");
    return (ENOMEM);
  }
  memset (map, 0, sizeof (*map));

  sstrncpy (map->type, ci->values[1].value.string, sizeof (map->type));
  if (ci->values_num == 3)
    sstrncpy (map->type_instance, ci->values[2].value.string,
        sizeof (map->type_instance));

  if (value_map == NULL)
  {
    value_map = c_avl_create ((void *) strcmp);
    if (value_map == NULL)
    {
      sfree (map);
      sfree (key);
      ERROR ("ethstat plugin: c_avl_create() failed.");
      return (-1);
    }
  }

  status = c_avl_insert (value_map,
      /* key = */ key,
      /* value = */ map);
  if (status != 0)
  {
    if (status > 0)
      ERROR ("ethstat plugin: Multiple mappings for \"%s\".", key);
    else
      ERROR ("ethstat plugin: c_avl_insert(\"%s\") failed.", key);

    sfree (map);
    sfree (key);
    return (-1);
  }

  return (0);
}