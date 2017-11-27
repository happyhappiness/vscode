static int powerdns_read_recursor (list_item_t *item) /* {{{ */
{
  char *buffer = NULL;
  size_t buffer_size = 0;
  int status;

  char *dummy;

  char *keys_list;
  char *key;
  char *key_saveptr;
  char *value;
  char *value_saveptr;

  if (item->command == NULL)
  {
    status = powerdns_update_recursor_command (item);
    if (status != 0)
    {
      ERROR ("powerdns plugin: powerdns_update_recursor_command failed.");
      return (-1);
    }

    DEBUG ("powerdns plugin: powerdns_read_recursor: item->command = %s;",
        item->command);
  }
  assert (item->command != NULL);

  status = powerdns_get_data (item, &buffer, &buffer_size);
  if (status != 0)
  {
    ERROR ("powerdns plugin: powerdns_get_data failed.");
    return (-1);
  }

  keys_list = strdup (item->command);
  if (keys_list == NULL)
  {
    FUNC_ERROR ("strdup");
    sfree (buffer);
    return (-1);
  }

  key_saveptr = NULL;
  value_saveptr = NULL;

  /* Skip the `get' at the beginning */
  strtok_r (keys_list, " \t", &key_saveptr);

  dummy = buffer;
  while ((value = strtok_r (dummy, " \t\n\r", &value_saveptr)) != NULL)
  {
    dummy = NULL;

    key = strtok_r (NULL, " \t", &key_saveptr);
    if (key == NULL)
      break;

    submit (item->instance, key, value);
  } /* while (strtok_r) */

  sfree (buffer);
  sfree (keys_list);

  return (0);
}