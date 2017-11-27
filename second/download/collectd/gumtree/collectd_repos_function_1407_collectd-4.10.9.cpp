static int udb_result_prepare_result (udb_result_t const *r, /* {{{ */
    udb_result_preparation_area_t *prep_area,
    char **column_names, size_t column_num)
{
  size_t i;

  if ((r == NULL) || (prep_area == NULL))
    return (-EINVAL);

  if (r->legacy_mode == 1)
    return (udb_legacy_result_prepare_result (r, prep_area,
          column_names, column_num));

  assert (r->legacy_mode == 0);

#define BAIL_OUT(status) \
  prep_area->ds = NULL; \
  sfree (prep_area->instances_pos); \
  sfree (prep_area->values_pos); \
  sfree (prep_area->instances_buffer); \
  sfree (prep_area->values_buffer); \
  return (status)

  /* Make sure previous preparations are cleaned up. */
  udb_result_finish_result (r, prep_area);
  prep_area->instances_pos = NULL;
  prep_area->values_pos = NULL;

  /* Read `ds' and check number of values {{{ */
  prep_area->ds = plugin_get_ds (r->type);
  if (prep_area->ds == NULL)
  {
    ERROR ("db query utils: udb_result_prepare_result: Type `%s' is not "
        "known by the daemon. See types.db(5) for details.",
        r->type);
    BAIL_OUT (-1);
  }

  if (((size_t) prep_area->ds->ds_num) != r->values_num)
  {
    ERROR ("db query utils: udb_result_prepare_result: The type `%s' "
        "requires exactly %i value%s, but the configuration specifies %zu.",
        r->type,
        prep_area->ds->ds_num, (prep_area->ds->ds_num == 1) ? "" : "s",
        r->values_num);
    BAIL_OUT (-1);
  }
  /* }}} */

  /* Allocate r->instances_pos, r->values_pos, r->instances_buffer, and
   * r->values_buffer {{{ */
  if (r->instances_num > 0)
  {
    prep_area->instances_pos
      = (size_t *) calloc (r->instances_num, sizeof (size_t));
    if (prep_area->instances_pos == NULL)
    {
      ERROR ("db query utils: udb_result_prepare_result: malloc failed.");
      BAIL_OUT (-ENOMEM);
    }

    prep_area->instances_buffer
      = (char **) calloc (r->instances_num, sizeof (char *));
    if (prep_area->instances_buffer == NULL)
    {
      ERROR ("db query utils: udb_result_prepare_result: malloc failed.");
      BAIL_OUT (-ENOMEM);
    }
  } /* if (r->instances_num > 0) */

  prep_area->values_pos
    = (size_t *) calloc (r->values_num, sizeof (size_t));
  if (prep_area->values_pos == NULL)
  {
    ERROR ("db query utils: udb_result_prepare_result: malloc failed.");
    BAIL_OUT (-ENOMEM);
  }

  prep_area->values_buffer
    = (char **) calloc (r->values_num, sizeof (char *));
  if (prep_area->values_buffer == NULL)
  {
    ERROR ("db query utils: udb_result_prepare_result: malloc failed.");
    BAIL_OUT (-ENOMEM);
  }
  /* }}} */

  /* Determine the position of the instance columns {{{ */
  for (i = 0; i < r->instances_num; i++)
  {
    size_t j;

    for (j = 0; j < column_num; j++)
    {
      if (strcasecmp (r->instances[i], column_names[j]) == 0)
      {
        prep_area->instances_pos[i] = j;
        break;
      }
    }

    if (j >= column_num)
    {
      ERROR ("db query utils: udb_result_prepare_result: "
          "Column `%s' could not be found.",
          r->instances[i]);
      BAIL_OUT (-ENOENT);
    }
  } /* }}} for (i = 0; i < r->instances_num; i++) */

  /* Determine the position of the value columns {{{ */
  for (i = 0; i < r->values_num; i++)
  {
    size_t j;

    for (j = 0; j < column_num; j++)
    {
      if (strcasecmp (r->values[i], column_names[j]) == 0)
      {
        prep_area->values_pos[i] = j;
        break;
      }
    }

    if (j >= column_num)
    {
      ERROR ("db query utils: udb_result_prepare_result: "
          "Column `%s' could not be found.",
          r->values[i]);
      BAIL_OUT (-ENOENT);
    }
  } /* }}} for (i = 0; i < r->values_num; i++) */

#undef BAIL_OUT
  return (0);
}