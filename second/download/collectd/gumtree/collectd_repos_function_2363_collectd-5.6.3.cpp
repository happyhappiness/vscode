int uc_get_hits(const data_set_t *ds, const value_list_t *vl) {
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int ret = STATE_ERROR;

  if (FORMAT_VL(name, sizeof(name), vl) != 0) {
    ERROR("uc_get_hits: FORMAT_VL failed.");
    return (STATE_ERROR);
  }

  pthread_mutex_lock(&cache_lock);

  if (c_avl_get(cache_tree, name, (void *)&ce) == 0) {
    assert(ce != NULL);
    ret = ce->hits;
  }

  pthread_mutex_unlock(&cache_lock);

  return (ret);
}