static void tr_action_destroy (tr_action_t *act) /* {{{ */
{
  if (act == NULL)
    return;

  regfree (&act->re);
  sfree (act->replacement);

  if (act->next != NULL)
    tr_action_destroy (act->next);

  sfree (act);
}