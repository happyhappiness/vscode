static int cdbi_config_add_database_driver_option (cdbi_database_t *db, /* {{{ */
    oconfig_item_t *ci)
{
  cdbi_driver_option_t *option;

  if ((ci->values_num != 2)
      || (ci->values[0].type != OCONFIG_TYPE_STRING)
      || (ci->values[1].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("dbi plugin: The `DriverOption' config option "
        "needs exactly two string arguments.");
    return (-1);
  }

  option = (cdbi_driver_option_t *) realloc (db->driver_options,
      sizeof (*option) * (db->driver_options_num + 1));
  if (option == NULL)
  {
    ERROR ("dbi plugin: realloc failed");
    return (-1);
  }

  db->driver_options = option;
  option = db->driver_options + db->driver_options_num;

  option->key = strdup (ci->values[0].value.string);
  if (option->key == NULL)
  {
    ERROR ("dbi plugin: strdup failed.");
    return (-1);
  }

  option->value = strdup (ci->values[1].value.string);
  if (option->value == NULL)
  {
    ERROR ("dbi plugin: strdup failed.");
    sfree (option->key);
    return (-1);
  }

  db->driver_options_num++;
  return (0);
}