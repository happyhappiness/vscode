static int fc_config_add_chain (const oconfig_item_t *ci) /* {{{ */
{
  fc_chain_t *chain = NULL;
  int status = 0;
  int i;
  int new_chain = 1;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("Filter subsystem: <Chain> blocks require exactly one "
        "string argument.");
    return (-1);
  }

  if (chain_list_head != NULL)
  {
    if ((chain = fc_chain_get_by_name (ci->values[0].value.string)) != NULL)
      new_chain = 0;
  }

  if (chain == NULL)
  {
    chain = (fc_chain_t *) malloc (sizeof (*chain));
    if (chain == NULL)
    {
      ERROR ("fc_config_add_chain: malloc failed.");
      return (-1);
    }
    memset (chain, 0, sizeof (*chain));
    sstrncpy (chain->name, ci->values[0].value.string, sizeof (chain->name));
    chain->rules = NULL;
    chain->targets = NULL;
    chain->next = NULL;
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Rule", option->key) == 0)
      status = fc_config_add_rule (chain, option);
    else if (strcasecmp ("Target", option->key) == 0)
      status = fc_config_add_target (&chain->targets, option);
    else
    {
      WARNING ("Filter subsystem: Chain %s: Option `%s' not allowed "
          "inside a <Chain> block.", chain->name, option->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (ci->children) */

  if (status != 0)
  {
    fc_free_chains (chain);
    return (-1);
  }

  if (chain_list_head != NULL)
  {
    if (!new_chain)
      return (0);

    fc_chain_t *ptr;

    ptr = chain_list_head;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = chain;
  }
  else
  {
    chain_list_head = chain;
  }

  return (0);
}