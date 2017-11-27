int uc_iterator_get_interval (uc_iter_t *iter, cdtime_t *ret_interval)
{
  if ((iter == NULL) || (iter->entry == NULL) || (ret_interval == NULL))
    return (-1);

  *ret_interval = iter->entry->interval;
  return (0);
}