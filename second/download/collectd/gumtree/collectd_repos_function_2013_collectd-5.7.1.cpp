udb_query_preparation_area_t *
udb_query_allocate_preparation_area(udb_query_t *q) /* {{{ */
{
  udb_query_preparation_area_t *q_area;
  udb_result_preparation_area_t **next_r_area;
  udb_result_t *r;

  q_area = calloc(1, sizeof(*q_area));
  if (q_area == NULL)
    return NULL;

  next_r_area = &q_area->result_prep_areas;
  for (r = q->results; r != NULL; r = r->next) {
    udb_result_preparation_area_t *r_area;

    r_area = calloc(1, sizeof(*r_area));
    if (r_area == NULL) {
      udb_result_preparation_area_t *a = q_area->result_prep_areas;

      while (a != NULL) {
        udb_result_preparation_area_t *next = a->next;
        sfree(a);
        a = next;
      }

      free(q_area);
      return NULL;
    }

    *next_r_area = r_area;
    next_r_area = &r_area->next;
  }

  return (q_area);
}