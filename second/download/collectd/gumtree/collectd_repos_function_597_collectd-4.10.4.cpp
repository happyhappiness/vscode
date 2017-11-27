static int fc_bit_write_create (const oconfig_item_t *ci, /* {{{ */
    void **user_data)
{
  int i;

  char **plugin_list;
  size_t plugin_list_len;

  plugin_list = NULL;
  plugin_list_len = 0;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    char **temp;
    int j;

    if (strcasecmp ("Plugin", child->key) != 0)
    {
      ERROR ("Filter subsystem: The built-in target `write' does not "
          "support the configuration option `%s'.",
          child->key);
      continue;
    }

    for (j = 0; j < child->values_num; j++)
    {
      if (child->values[j].type != OCONFIG_TYPE_STRING)
      {
        ERROR ("Filter subsystem: Built-in target `write': "
            "The `Plugin' option accepts only string arguments.");
        continue;
      }

      temp = (char **) realloc (plugin_list, (plugin_list_len + 2)
          * (sizeof (*plugin_list)));
      if (temp == NULL)
      {
        ERROR ("fc_bit_write_create: realloc failed.");
        continue;
      }
      plugin_list = temp;

      plugin_list[plugin_list_len] = fc_strdup (child->values[j].value.string);
      if (plugin_list[plugin_list_len] == NULL)
      {
        ERROR ("fc_bit_write_create: fc_strdup failed.");
        continue;
      }
      plugin_list_len++;
      plugin_list[plugin_list_len] = NULL;
    } /* for (j = 0; j < child->values_num; j++) */
  } /* for (i = 0; i < ci->children_num; i++) */

  *user_data = plugin_list;

  return (0);
}