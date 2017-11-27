static int powerdns_update_recursor_command (list_item_t *li) /* {{{ */
{
  char buffer[4096];
  int status;

  if (li == NULL)
    return (0);

  if (li->fields_num < 1)
  {
    sstrncpy (buffer, RECURSOR_COMMAND, sizeof (buffer));
  }
  else
  {
    strcpy (buffer, "get ");
    status = strjoin (&buffer[4], sizeof (buffer) - strlen ("get "),
	li->fields, li->fields_num,
	/* seperator = */ " ");
    if (status < 0)
    {
      ERROR ("powerdns plugin: strjoin failed.");
      return (-1);
    }
  }

  buffer[sizeof (buffer) - 1] = 0;
  li->command = strdup (buffer);
  if (li->command == NULL)
  {
    ERROR ("powerdns plugin: strdup failed.");
    return (-1);
  }

  return (0);
}