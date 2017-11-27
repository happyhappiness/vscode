int uc_iterator_get_meta(uc_iter_t *iter, meta_data_t **ret_meta) {
  if ((iter == NULL) || (iter->entry == NULL) || (ret_meta == NULL))
    return -1;

  *ret_meta = meta_data_clone(iter->entry->meta);

  return 0;
}