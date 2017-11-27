int uc_iterator_next(uc_iter_t *iter, char **ret_name) {
  int status;

  if (iter == NULL)
    return (-1);

  while ((status = c_avl_iterator_next(iter->iter, (void *)&iter->name,
                                       (void *)&iter->entry)) == 0) {
    if (iter->entry->state == STATE_MISSING)
      continue;

    break;
  }
  if (status != 0) {
    iter->name = NULL;
    iter->entry = NULL;
    return (-1);
  }

  if (ret_name != NULL)
    *ret_name = iter->name;

  return (0);
}