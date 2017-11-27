int uc_set_state(const data_set_t *ds, const value_list_t *vl, int state) {
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int ret = -1;

  if (FORMAT_VL(name, sizeof(name), vl) != 0) {
    ERROR("uc_set_state: FORMAT_VL failed.");
    return (STATE_ERROR);
  }

  pthread_mutex_lock(&cache_lock);

  if (c_avl_get(cache_tree, name, (void *)&ce) == 0) {
    assert(ce != NULL);
    ret = ce->state;
    ce->state = state;
  }

  pthread_mutex_unlock(&cache_lock);

  return (ret);
}