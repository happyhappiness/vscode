int ut_search_threshold(const value_list_t *vl, /* {{{ */
                        threshold_t *ret_threshold) {
  threshold_t *t;

  if (vl == NULL)
    return (EINVAL);

  /* Is this lock really necessary? */
  pthread_mutex_lock(&threshold_lock);
  t = threshold_search(vl);
  if (t == NULL) {
    pthread_mutex_unlock(&threshold_lock);
    return (ENOENT);
  }

  memcpy(ret_threshold, t, sizeof(*ret_threshold));
  pthread_mutex_unlock(&threshold_lock);

  ret_threshold->next = NULL;

  return (0);
}