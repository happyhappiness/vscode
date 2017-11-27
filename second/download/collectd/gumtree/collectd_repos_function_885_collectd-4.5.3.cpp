static int ut_check_one_data_source (const data_set_t *ds,
    const value_list_t *vl,
    const threshold_t *th,
    const gauge_t *values,
    int ds_index)
{ /* {{{ */
  const char *ds_name;
  int is_warning = 0;
  int is_failure = 0;

  /* check if this threshold applies to this data source */
  ds_name = ds->ds[ds_index].name;
  if ((th->data_source[0] != 0)
      && (strcmp (ds_name, th->data_source) != 0))
    return (STATE_OKAY);

  if ((th->flags & UT_FLAG_INVERT) != 0)
  {
    is_warning--;
    is_failure--;
  }

  if ((!isnan (th->failure_min) && (th->failure_min > values[ds_index]))
      || (!isnan (th->failure_max) && (th->failure_max < values[ds_index])))
    is_failure++;
  if (is_failure != 0)
    return (STATE_ERROR);

  if ((!isnan (th->warning_min) && (th->warning_min > values[ds_index]))
      || (!isnan (th->warning_max) && (th->warning_max < values[ds_index])))
    is_warning++;
  if (is_warning != 0)
    return (STATE_WARNING);

  return (STATE_OKAY);
}