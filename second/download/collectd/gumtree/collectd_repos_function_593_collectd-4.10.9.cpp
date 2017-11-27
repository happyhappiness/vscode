static void fc_free_targets (fc_target_t *t) /* {{{ */
{
  if (t == NULL)
    return;

  if (t->proc.destroy != NULL)
    (*t->proc.destroy) (&t->user_data);
  else if (t->user_data != NULL)
  {
    ERROR ("Filter subsystem: fc_free_targets: There is user data, but no "
        "destroy functions has been specified. "
        "Memory will probably be lost!");
  }

  if (t->next != NULL)
    fc_free_targets (t->next);

  free (t);
}