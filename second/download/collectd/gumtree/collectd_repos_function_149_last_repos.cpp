int write_riemann_threshold_check(const data_set_t *ds, const value_list_t *vl,
                                  int *statuses) { /* {{{ */
  threshold_t *th;
  gauge_t *values;
  int status;

  assert(vl->values_len > 0);
  memset(statuses, 0, vl->values_len * sizeof(*statuses));

  if (threshold_tree == NULL)
    return 0;

  /* Is this lock really necessary? So far, thresholds are only inserted at
   * startup. -octo */
  pthread_mutex_lock(&threshold_lock);
  th = threshold_search(vl);
  pthread_mutex_unlock(&threshold_lock);
  if (th == NULL)
    return 0;

  DEBUG("ut_check_threshold: Found matching threshold(s)");

  values = uc_get_rate(ds, vl);
  if (values == NULL)
    return 0;

  while (th != NULL) {
    status = ut_check_one_threshold(ds, vl, th, values, statuses);
    if (status < 0) {
      ERROR("ut_check_threshold: ut_check_one_threshold failed.");
      sfree(values);
      return -1;
    }

    th = th->next;
  } /* while (th) */

  sfree(values);

  return 0;
}