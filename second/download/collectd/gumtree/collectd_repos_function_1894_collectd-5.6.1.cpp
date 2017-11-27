int udb_query_handle_result (udb_query_t const *q, /* {{{ */
    udb_query_preparation_area_t *prep_area, char **column_values)
{
  udb_result_preparation_area_t *r_area;
  udb_result_t *r;
  int success;
  int status;

  if ((q == NULL) || (prep_area == NULL))
    return (-EINVAL);

  if ((prep_area->column_num < 1) || (prep_area->host == NULL)
      || (prep_area->plugin == NULL) || (prep_area->db_name == NULL))
  {
    ERROR ("db query utils: Query `%s': Query is not prepared; "
        "can't handle result.", q->name);
    return (-EINVAL);
  }

#if defined(COLLECT_DEBUG) && COLLECT_DEBUG /* {{{ */
  do
  {
    for (size_t i = 0; i < prep_area->column_num; i++)
    {
      DEBUG ("db query utils: udb_query_handle_result (%s, %s): "
          "column[%zu] = %s;",
          prep_area->db_name, q->name, i, column_values[i]);
    }
  } while (0);
#endif /* }}} */

  success = 0;
  for (r = q->results, r_area = prep_area->result_prep_areas;
      r != NULL; r = r->next, r_area = r_area->next)
  {
    status = udb_result_handle_result (r, prep_area, r_area,
        q, column_values);
    if (status == 0)
      success++;
  }

  if (success == 0)
  {
    ERROR ("db query utils: udb_query_handle_result (%s, %s): "
        "All results failed.", prep_area->db_name, q->name);
    return (-1);
  }

  return (0);
}