int uc_iterator_get_time(uc_iter_t *iter, cdtime_t *ret_time) {
  if ((iter == NULL) || (iter->entry == NULL) || (ret_time == NULL))
    return (-1);

  *ret_time = iter->entry->last_time;
  return (0);
}