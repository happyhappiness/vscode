static int udb_legacy_result_prepare_result (udb_result_t const *r, /* {{{ */
    udb_result_preparation_area_t *prep_area,
    char **column_names, size_t column_num)
{
  if (r == NULL)
    return (-EINVAL);

  assert (r->legacy_mode == 1);

  /* Make sure previous preparations are cleaned up. */
  udb_legacy_result_finish_result (r, prep_area);

  if (r->legacy_position >= column_num)
  {
    ERROR ("db query utils: The legacy configuration specified (at least) "
        "%zu `Column's, but the query returned only %zu columns!",
        r->legacy_position + 1, column_num);
    return (-ENOENT);
  }

  /* Read `ds' and check number of values {{{ */
  prep_area->ds = plugin_get_ds (r->type);
  if (prep_area->ds == NULL)
  {
    ERROR ("db query utils: udb_result_prepare_result: Type `%s' is not "
        "known by the daemon. See types.db(5) for details.",
        r->type);
    return (-1);
  }

  if (prep_area->ds->ds_num != 1)
  {
    ERROR ("db query utils: udb_result_prepare_result: The type `%s' "
        "requires exactly %i values, but the legacy configuration "
        "requires exactly one!",
        r->type,
        prep_area->ds->ds_num);
    return (-1);
  }
  /* }}} */

  return (0);
}