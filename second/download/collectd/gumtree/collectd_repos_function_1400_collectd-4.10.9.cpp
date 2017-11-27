static void udb_legacy_result_finish_result (udb_result_t const *r, /* {{{ */
    udb_result_preparation_area_t *prep_area)
{
  if ((r == NULL) || (prep_area))
    return;

  assert (r->legacy_mode == 1);

  prep_area->ds = NULL;
}