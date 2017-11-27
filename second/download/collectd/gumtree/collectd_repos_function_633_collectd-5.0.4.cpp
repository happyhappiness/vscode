static void fc_free_rules (fc_rule_t *r) /* {{{ */
{
  if (r == NULL)
    return;

  fc_free_matches (r->matches);
  fc_free_targets (r->targets);

  if (r->next != NULL)
    fc_free_rules (r->next);

  free (r);
}