int ut_check_threshold (const data_set_t *ds, const value_list_t *vl)
{ /* {{{ */
  threshold_t *th;
  gauge_t *values;
  int status;

  int worst_state = -1;
  threshold_t *worst_th = NULL;
  int worst_ds_index = -1;

  if (threshold_tree == NULL)
    return (0);

  /* Is this lock really necessary? So far, thresholds are only inserted at
   * startup. -octo */
  pthread_mutex_lock (&threshold_lock);
  th = threshold_search (vl);
  pthread_mutex_unlock (&threshold_lock);
  if (th == NULL)
    return (0);

  DEBUG ("ut_check_threshold: Found matching threshold(s)");

  values = uc_get_rate (ds, vl);
  if (values == NULL)
    return (0);

  while (th != NULL)
  {
    int ds_index = -1;

    status = ut_check_one_threshold (ds, vl, th, values, &ds_index);
    if (status < 0)
    {
      ERROR ("ut_check_threshold: ut_check_one_threshold failed.");
      sfree (values);
      return (-1);
    }

    if (worst_state < status)
    {
      worst_state = status;
      worst_th = th;
      worst_ds_index = ds_index;
    }

    th = th->next;
  } /* while (th) */

  status = ut_report_state (ds, vl, worst_th, values,
      worst_ds_index, worst_state);
  if (status != 0)
  {
    ERROR ("ut_check_threshold: ut_report_state failed.");
    sfree (values);
    return (-1);
  }

  sfree (values);

  return (0);
}