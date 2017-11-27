static void udb_legacy_result_finish_result (udb_result_t *r) /* {{{ */
{
  if (r == NULL)
    return;

  assert (r->legacy_mode == 1);

  r->ds = NULL;
}