udb_query_preparation_area_t *
udb_query_allocate_preparation_area (udb_query_t *q) /* {{{ */
{
  udb_query_preparation_area_t   *q_area;
  udb_result_preparation_area_t **next_r_area;
  udb_result_t *r;

  q_area = (udb_query_preparation_area_t *)malloc (sizeof (*q_area));
  if (q_area == NULL)
    return NULL;

  memset (q_area, 0, sizeof (*q_area));

  next_r_area = &q_area->result_prep_areas;
  for (r = q->results; r != NULL; r = r->next)
  {
    udb_result_preparation_area_t *r_area;

    r_area = (udb_result_preparation_area_t *)malloc (sizeof (*r_area));
    if (r_area == NULL)
    {
      for (r_area = q_area->result_prep_areas;
          r_area != NULL; r_area = r_area->next)
      {
        free (r_area);
      }
      free (q_area);
      return NULL;
    }

    memset (r_area, 0, sizeof (*r_area));

    *next_r_area = r_area;
    next_r_area  = &r_area->next;
  }

  return (q_area);
}