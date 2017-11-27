void
udb_query_delete_preparation_area (udb_query_preparation_area_t *q_area) /* {{{ */
{
  udb_result_preparation_area_t *r_area;

  if (q_area == NULL)
    return;

  r_area = q_area->result_prep_areas;
  while (r_area != NULL)
  {
    udb_result_preparation_area_t *area = r_area;

    r_area = r_area->next;

    sfree (area->instances_pos);
    sfree (area->values_pos);
    sfree (area->instances_buffer);
    sfree (area->values_buffer);
    free (area);
  }

  sfree (q_area->host);
  sfree (q_area->plugin);
  sfree (q_area->db_name);

  free (q_area);
}