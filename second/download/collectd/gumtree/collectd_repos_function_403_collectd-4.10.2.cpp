int uc_get_history_by_name (const char *name,
    gauge_t *ret_history, size_t num_steps, size_t num_ds)
{
  cache_entry_t *ce = NULL;
  size_t i;
  int status = 0;

  pthread_mutex_lock (&cache_lock);

  status = c_avl_get (cache_tree, name, (void *) &ce);
  if (status != 0)
  {
    pthread_mutex_unlock (&cache_lock);
    return (-ENOENT);
  }

  if (((size_t) ce->values_num) != num_ds)
  {
    pthread_mutex_unlock (&cache_lock);
    return (-EINVAL);
  }

  /* Check if there are enough values available. If not, increase the buffer
   * size. */
  if (ce->history_length < num_steps)
  {
    gauge_t *tmp;
    size_t i;

    tmp = realloc (ce->history, sizeof (*ce->history)
	* num_steps * ce->values_num);
    if (tmp == NULL)
    {
      pthread_mutex_unlock (&cache_lock);
      return (-ENOMEM);
    }

    for (i = ce->history_length * ce->values_num;
	i < (num_steps * ce->values_num);
	i++)
      tmp[i] = NAN;

    ce->history = tmp;
    ce->history_length = num_steps;
  } /* if (ce->history_length < num_steps) */

  /* Copy the values to the output buffer. */
  for (i = 0; i < num_steps; i++)
  {
    size_t src_index;
    size_t dst_index;

    if (i < ce->history_index)
      src_index = ce->history_index - (i + 1);
    else
      src_index = ce->history_length + ce->history_index - (i + 1);
    src_index = src_index * num_ds;

    dst_index = i * num_ds;

    memcpy (ret_history + dst_index, ce->history + src_index,
	sizeof (*ret_history) * num_ds);
  }

  pthread_mutex_unlock (&cache_lock);

  return (0);
}