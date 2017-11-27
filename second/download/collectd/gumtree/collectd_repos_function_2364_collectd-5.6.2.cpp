uc_iter_t *uc_get_iterator(void) {
  uc_iter_t *iter;

  iter = (uc_iter_t *)calloc(1, sizeof(*iter));
  if (iter == NULL)
    return (NULL);

  pthread_mutex_lock(&cache_lock);

  iter->iter = c_avl_get_iterator(cache_tree);
  if (iter->iter == NULL) {
    free(iter);
    return (NULL);
  }

  return (iter);
}