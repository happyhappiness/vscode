size_t uc_get_size(void) {
  size_t size_arrays = 0;

  pthread_mutex_lock(&cache_lock);
  size_arrays = (size_t)c_avl_size(cache_tree);
  pthread_mutex_unlock(&cache_lock);

  return size_arrays;
}