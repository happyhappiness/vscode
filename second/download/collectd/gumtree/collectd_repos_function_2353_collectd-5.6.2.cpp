int uc_get_rate_by_name(const char *name, gauge_t **ret_values,
                        size_t *ret_values_num) {
  gauge_t *ret = NULL;
  size_t ret_num = 0;
  cache_entry_t *ce = NULL;
  int status = 0;

  pthread_mutex_lock(&cache_lock);

  if (c_avl_get(cache_tree, name, (void *)&ce) == 0) {
    assert(ce != NULL);

    /* remove missing values from getval */
    if (ce->state == STATE_MISSING) {
      status = -1;
    } else {
      ret_num = ce->values_num;
      ret = malloc(ret_num * sizeof(*ret));
      if (ret == NULL) {
        ERROR("utils_cache: uc_get_rate_by_name: malloc failed.");
        status = -1;
      } else {
        memcpy(ret, ce->values_gauge, ret_num * sizeof(gauge_t));
      }
    }
  } else {
    DEBUG("utils_cache: uc_get_rate_by_name: No such value: %s", name);
    status = -1;
  }

  pthread_mutex_unlock(&cache_lock);

  if (status == 0) {
    *ret_values = ret;
    *ret_values_num = ret_num;
  }

  return (status);
}