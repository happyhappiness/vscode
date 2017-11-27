static void mv_free_match (mv_match_t *m) /* {{{ */
{
  if (m == NULL)
    return;

  free (m);
}