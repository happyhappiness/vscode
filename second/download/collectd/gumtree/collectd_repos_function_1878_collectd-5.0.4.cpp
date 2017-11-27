int lcc_string_to_identifier (lcc_connection_t *c, /* {{{ */
    lcc_identifier_t *ident, const char *string)
{
  char *string_copy;
  char *host;
  char *plugin;
  char *plugin_instance;
  char *type;
  char *type_instance;

  string_copy = strdup (string);
  if (string_copy == NULL)
  {
    lcc_set_errno (c, ENOMEM);
    return (-1);
  }

  host = string_copy;
  plugin = strchr (host, '/');
  if (plugin == NULL)
  {
    LCC_SET_ERRSTR (c, "Malformed identifier string: %s", string);
    free (string_copy);
    return (-1);
  }
  *plugin = 0;
  plugin++;

  type = strchr (plugin, '/');
  if (type == NULL)
  {
    LCC_SET_ERRSTR (c, "Malformed identifier string: %s", string);
    free (string_copy);
    return (-1);
  }
  *type = 0;
  type++;

  plugin_instance = strchr (plugin, '-');
  if (plugin_instance != NULL)
  {
    *plugin_instance = 0;
    plugin_instance++;
  }

  type_instance = strchr (type, '-');
  if (type_instance != NULL)
  {
    *type_instance = 0;
    type_instance++;
  }

  memset (ident, 0, sizeof (*ident));

  SSTRCPY (ident->host, host);
  SSTRCPY (ident->plugin, plugin);
  if (plugin_instance != NULL)
    SSTRCPY (ident->plugin_instance, plugin_instance);
  SSTRCPY (ident->type, type);
  if (type_instance != NULL)
    SSTRCPY (ident->type_instance, type_instance);

  free (string_copy);
  return (0);
}