fc_chain_t *fc_chain_get_by_name (const char *chain_name) /* {{{ */
{
  if (chain_name == NULL)
    return (NULL);

  for (fc_chain_t *chain = chain_list_head; chain != NULL; chain = chain->next)
    if (strcasecmp (chain_name, chain->name) == 0)
      return (chain);

  return (NULL);
}