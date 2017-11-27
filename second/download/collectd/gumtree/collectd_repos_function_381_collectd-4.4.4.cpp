static int powerdns_config_add_collect (list_item_t *li, /* {{{ */
    oconfig_item_t *ci)
{
  int i;
  char **temp;

  if (ci->values_num < 1)
  {
    WARNING ("powerdns plugin: The `Collect' option needs "
	"at least one argument.");
    return (-1);
  }

  for (i = 0; i < ci->values_num; i++)
    if (ci->values[i].type != OCONFIG_TYPE_STRING)
    {
      WARNING ("powerdns plugin: Only string arguments are allowed to "
	  "the `Collect' option.");
      return (-1);
    }

  temp = (char **) realloc (li->fields,
      sizeof (char *) * (li->fields_num + ci->values_num));
  if (temp == NULL)
  {
    WARNING ("powerdns plugin: realloc failed.");
    return (-1);
  }
  li->fields = temp;

  for (i = 0; i < ci->values_num; i++)
  {
    li->fields[li->fields_num] = strdup (ci->values[i].value.string);
    if (li->fields[li->fields_num] == NULL)
    {
      WARNING ("powerdns plugin: strdup failed.");
      continue;
    }
    li->fields_num++;
  }

  /* Invalidate a previously computed command */
  sfree (li->command);

  return (0);
}