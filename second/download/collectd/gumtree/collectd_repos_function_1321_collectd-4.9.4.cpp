static void udb_result_finish_result (udb_result_t *r) /* {{{ */
{
  if (r == NULL)
    return;

  if (r->legacy_mode == 1)
  {
    udb_legacy_result_finish_result (r);
    return;
  }

  assert (r->legacy_mode == 0);

  r->ds = NULL;
  sfree (r->instances_pos);
  sfree (r->values_pos);
  sfree (r->instances_buffer);
  sfree (r->values_buffer);
}