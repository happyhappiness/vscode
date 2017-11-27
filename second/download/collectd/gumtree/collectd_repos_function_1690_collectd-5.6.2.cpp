static int ut_check_one_threshold(const data_set_t *ds, const value_list_t *vl,
                                  const threshold_t *th, const gauge_t *values,
                                  int *ret_ds_index) { /* {{{ */
  int ret = -1;
  int ds_index = -1;
  gauge_t values_copy[ds->ds_num];

  memcpy(values_copy, values, sizeof(values_copy));

  if ((th->flags & UT_FLAG_PERCENTAGE) != 0) {
    int num = 0;
    gauge_t sum = 0.0;

    if (ds->ds_num == 1) {
      WARNING(
          "ut_check_one_threshold: The %s type has only one data "
          "source, but you have configured to check this as a percentage. "
          "That doesn't make much sense, because the percentage will always "
          "be 100%%!",
          ds->type);
    }

    /* Prepare `sum' and `num'. */
    for (size_t i = 0; i < ds->ds_num; i++)
      if (!isnan(values[i])) {
        num++;
        sum += values[i];
      }

    if ((num == 0)       /* All data sources are undefined. */
        || (sum == 0.0)) /* Sum is zero, cannot calculate percentage. */
    {
      for (size_t i = 0; i < ds->ds_num; i++)
        values_copy[i] = NAN;
    } else /* We can actually calculate the percentage. */
    {
      for (size_t i = 0; i < ds->ds_num; i++)
        values_copy[i] = 100.0 * values[i] / sum;
    }
  } /* if (UT_FLAG_PERCENTAGE) */

  for (size_t i = 0; i < ds->ds_num; i++) {
    int status;

    status = ut_check_one_data_source(ds, vl, th, values_copy, i);
    if (ret < status) {
      ret = status;
      ds_index = i;
    }
  } /* for (ds->ds_num) */

  if (ret_ds_index != NULL)
    *ret_ds_index = ds_index;

  return (ret);
}