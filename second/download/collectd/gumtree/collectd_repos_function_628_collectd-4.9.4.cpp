static int bind_xml_table_callback (const char *name, value_t value, /* {{{ */
    time_t current_time, void *user_data)
{
  translation_table_ptr_t *table = (translation_table_ptr_t *) user_data;
  size_t i;

  if (table == NULL)
    return (-1);

  for (i = 0; i < table->table_length; i++)
  {
    if (strcmp (table->table[i].xml_name, name) != 0)
      continue;

    submit (current_time,
        table->plugin_instance,
        table->table[i].type,
        table->table[i].type_instance,
        value);
    break;
  }

  return (0);
}