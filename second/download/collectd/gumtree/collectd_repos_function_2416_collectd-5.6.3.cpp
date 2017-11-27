static void fc_free_matches(fc_match_t *m) /* {{{ */
{
  if (m == NULL)
    return;

  if (m->proc.destroy != NULL)
    (*m->proc.destroy)(&m->user_data);
  else if (m->user_data != NULL) {
    ERROR("Filter subsystem: fc_free_matches: There is user data, but no "
          "destroy functions has been specified. "
          "Memory will probably be lost!");
  }

  if (m->next != NULL)
    fc_free_matches(m->next);

  free(m);
}