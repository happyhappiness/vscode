int uc_get_names(char ***ret_names, cdtime_t **ret_times, size_t *ret_number) {
  c_avl_iterator_t *iter;
  char *key;
  cache_entry_t *value;

  char **names = NULL;
  cdtime_t *times = NULL;
  size_t number = 0;
  size_t size_arrays = 0;

  int status = 0;

  if ((ret_names == NULL) || (ret_number == NULL))
    return -1;

  pthread_mutex_lock(&cache_lock);

  size_arrays = (size_t)c_avl_size(cache_tree);
  if (size_arrays < 1) {
    /* Handle the "no values" case here, to avoid the error message when
     * calloc() returns NULL. */
    pthread_mutex_unlock(&cache_lock);
    return 0;
  }

  names = calloc(size_arrays, sizeof(*names));
  times = calloc(size_arrays, sizeof(*times));
  if ((names == NULL) || (times == NULL)) {
    ERROR("uc_get_names: calloc failed.");
    sfree(names);
    sfree(times);
    pthread_mutex_unlock(&cache_lock);
    return ENOMEM;
  }

  iter = c_avl_get_iterator(cache_tree);
  while (c_avl_iterator_next(iter, (void *)&key, (void *)&value) == 0) {
    /* remove missing values when list values */
    if (value->state == STATE_MISSING)
      continue;

    /* c_avl_size does not return a number smaller than the number of elements
     * returned by c_avl_iterator_next. */
    assert(number < size_arrays);

    if (ret_times != NULL)
      times[number] = value->last_time;

    names[number] = strdup(key);
    if (names[number] == NULL) {
      status = -1;
      break;
    }

    number++;
  } /* while (c_avl_iterator_next) */

  c_avl_iterator_destroy(iter);
  pthread_mutex_unlock(&cache_lock);

  if (status != 0) {
    for (size_t i = 0; i < number; i++) {
      sfree(names[i]);
    }
    sfree(names);
    sfree(times);

    return -1;
  }

  *ret_names = names;
  if (ret_times != NULL)
    *ret_times = times;
  else
    sfree(times);
  *ret_number = number;

  return 0;
}