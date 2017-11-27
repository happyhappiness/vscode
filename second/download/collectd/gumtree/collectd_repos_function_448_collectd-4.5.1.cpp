static int powerdns_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  DEBUG ("powerdns plugin: powerdns_config (ci = %p);", (void *) ci);

  if (list == NULL)
  {
    list = llist_create ();

    if (list == NULL)
    {
      ERROR ("powerdns plugin: `llist_create' failed.");
      return (-1);
    }
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if ((strcasecmp ("Server", option->key) == 0)
	|| (strcasecmp ("Recursor", option->key) == 0))
      powerdns_config_add_server (option);
    else if (strcasecmp ("LocalSocket", option->key) == 0)
    {
      char *temp = strdup (option->key);
      if (temp == NULL)
        return (1);
      sfree (local_sockpath);
      local_sockpath = temp;
    }
    else
    {
      ERROR ("powerdns plugin: Option `%s' not allowed here.", option->key);
    }
  } /* for (i = 0; i < ci->children_num; i++) */

  return (0);
}