static void udb_result_finish_result (const udb_result_t const *r, /* {{{ */
    udb_result_preparation_area_t *prep_area)
{
  if ((r == NULL) || (prep_area == NULL))
    return;

  if (r->legacy_mode == 1)
  {
    udb_legacy_result_finish_result (r, prep_area);
    return;
  }

  assert (r->legacy_mode == 0);

  prep_area->ds = NULL;
  sfree (prep_area->instances_pos);
  sfree (prep_area->values_pos);
  sfree (prep_area->instances_buffer);
  sfree (prep_area->values_buffer);
}