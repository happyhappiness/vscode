static int udb_result_handle_result (udb_result_t *r, /* {{{ */
    udb_query_preparation_area_t *q_area,
    udb_result_preparation_area_t *r_area,
    udb_query_t const *q, char **column_values)
{
  assert (r && q_area && r_area);

  for (size_t i = 0; i < r->instances_num; i++)
    r_area->instances_buffer[i] = column_values[r_area->instances_pos[i]];

  for (size_t i = 0; i < r->values_num; i++)
    r_area->values_buffer[i] = column_values[r_area->values_pos[i]];

  for (size_t i = 0; i < r->metadata_num; i++)
    r_area->metadata_buffer[i] = column_values[r_area->metadata_pos[i]];

  if (q->plugin_instance_from)
    r_area->plugin_instance = column_values[q_area->plugin_instance_pos];

  return udb_result_submit (r, r_area, q, q_area);
}