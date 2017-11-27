static int ut_check_one_threshold (const data_set_t *ds,
    const value_list_t *vl,
    const threshold_t *th,
    const gauge_t *values,
    int *ret_ds_index)
{ /* {{{ */
  int ret = -1;
  int ds_index = -1;
  int i;

  for (i = 0; i < ds->ds_num; i++)
  {
    int status;

    status = ut_check_one_data_source (ds, vl, th, values, i);
    if (ret < status)
    {
      ret = status;
      ds_index = i;
    }
  } /* for (ds->ds_num) */

  if (ret_ds_index != NULL)
    *ret_ds_index = ds_index;

  return (ret);
}