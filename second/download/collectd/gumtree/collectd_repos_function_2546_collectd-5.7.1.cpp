static void fc_free_chains(fc_chain_t *c) /* {{{ */
{
  if (c == NULL)
    return;

  fc_free_rules(c->rules);
  fc_free_targets(c->targets);

  if (c->next != NULL)
    fc_free_chains(c->next);

  free(c);
}