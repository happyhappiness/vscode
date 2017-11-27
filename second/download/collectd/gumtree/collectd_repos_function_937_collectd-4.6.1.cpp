static int udb_result_handle_result (udb_result_t *r, /* {{{ */
    udb_query_t *q, char **column_values)
{
  size_t i;

  if (r->legacy_mode == 1)
    return (udb_legacy_result_handle_result (r, q, column_values));

  assert (r->legacy_mode == 0);

  for (i = 0; i < r->instances_num; i++)
    r->instances_buffer[i] = column_values[r->instances_pos[i]];

  for (i = 0; i < r->values_num; i++)
    r->values_buffer[i] = column_values[r->values_pos[i]];

  udb_result_submit (r, q);

  return (0);
}