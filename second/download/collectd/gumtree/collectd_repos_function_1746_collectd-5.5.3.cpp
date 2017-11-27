static void udb_result_finish_result (udb_result_t const *r, /* {{{ */
    udb_result_preparation_area_t *prep_area)
{
  if ((r == NULL) || (prep_area == NULL))
    return;

  prep_area->ds = NULL;
  sfree (prep_area->instances_pos);
  sfree (prep_area->values_pos);
  sfree (prep_area->metadata_pos);
  sfree (prep_area->instances_buffer);
  sfree (prep_area->values_buffer);
  sfree (prep_area->metadata_buffer);
}