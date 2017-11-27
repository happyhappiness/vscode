static int fc_bit_write_create (const oconfig_item_t *ci, /* {{{ */
    void **user_data)
{
  int i;

  fc_writer_t *plugin_list = NULL;
  size_t plugin_list_len = 0;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    fc_writer_t *temp;
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
      char *plugin;

      if (child->values[j].type != OCONFIG_TYPE_STRING)
      {
        ERROR ("Filter subsystem: Built-in target `write': "
            "The `Plugin' option accepts only string arguments.");
        continue;
      }
      plugin = child->values[j].value.string;

      temp = (fc_writer_t *) realloc (plugin_list, (plugin_list_len + 2)
          * (sizeof (*plugin_list)));
      if (temp == NULL)
      {
        ERROR ("fc_bit_write_create: realloc failed.");
        continue;
      }
      plugin_list = temp;

      plugin_list[plugin_list_len].plugin = fc_strdup (plugin);
      if (plugin_list[plugin_list_len].plugin == NULL)
      {
        ERROR ("fc_bit_write_create: fc_strdup failed.");
        continue;
      }
      C_COMPLAIN_INIT (&plugin_list[plugin_list_len].complaint);
      plugin_list_len++;
      plugin_list[plugin_list_len].plugin = NULL;
    } /* for (j = 0; j < child->values_num; j++) */
  } /* for (i = 0; i < ci->children_num; i++) */

  *user_data = plugin_list;

  return (0);
}