void udb_query_finish_result (udb_query_t const *q, /* {{{ */
    udb_query_preparation_area_t *prep_area)
{
  udb_result_preparation_area_t *r_area;
  udb_result_t *r;

  if ((q == NULL) || (prep_area == NULL))
    return;

  prep_area->column_num = 0;
  sfree (prep_area->host);
  sfree (prep_area->plugin);
  sfree (prep_area->db_name);

  prep_area->interval = -1;

  for (r = q->results, r_area = prep_area->result_prep_areas;
      r != NULL; r = r->next, r_area = r_area->next)
  {
    /* this may happen during error conditions of the caller */
    if (r_area == NULL)
      break;
    udb_result_finish_result (r, r_area);
  }
}