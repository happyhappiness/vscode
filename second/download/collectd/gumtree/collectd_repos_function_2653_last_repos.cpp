static meta_data_t *uc_get_meta(const value_list_t *vl) /* {{{ */
{
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int status;

  status = FORMAT_VL(name, sizeof(name), vl);
  if (status != 0) {
    ERROR("utils_cache: uc_get_meta: FORMAT_VL failed.");
    return NULL;
  }

  pthread_mutex_lock(&cache_lock);

  status = c_avl_get(cache_tree, name, (void *)&ce);
  if (status != 0) {
    pthread_mutex_unlock(&cache_lock);
    return NULL;
  }
  assert(ce != NULL);

  if (ce->meta == NULL)
    ce->meta = meta_data_create();

  if (ce->meta == NULL)
    pthread_mutex_unlock(&cache_lock);

  return ce->meta;
}