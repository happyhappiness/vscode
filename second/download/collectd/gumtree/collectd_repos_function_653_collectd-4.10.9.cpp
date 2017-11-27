static int bind_config_add_view_zone (cb_view_t *view, /* {{{ */
    oconfig_item_t *ci)
{
  char **tmp;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("bind plugin: The `Zone' option needs "
        "exactly one string argument.");
    return (-1);
  }

  tmp = (char **) realloc (view->zones,
      sizeof (char *) * (view->zones_num + 1));
  if (tmp == NULL)
  {
    ERROR ("bind plugin: realloc failed.");
    return (-1);
  }
  view->zones = tmp;

  view->zones[view->zones_num] = strdup (ci->values[0].value.string);
  if (view->zones[view->zones_num] == NULL)
  {
    ERROR ("bind plugin: strdup failed.");
    return (-1);
  }
  view->zones_num++;

  return (0);
}