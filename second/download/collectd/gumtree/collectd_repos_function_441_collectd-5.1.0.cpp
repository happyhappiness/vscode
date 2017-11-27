int uc_get_names (char ***ret_names, cdtime_t **ret_times, size_t *ret_number)
{
  c_avl_iterator_t *iter;
  char *key;
  cache_entry_t *value;

  char **names = NULL;
  cdtime_t *times = NULL;
  size_t number = 0;

  int status = 0;

  if ((ret_names == NULL) || (ret_number == NULL))
    return (-1);

  pthread_mutex_lock (&cache_lock);

  iter = c_avl_get_iterator (cache_tree);
  while (c_avl_iterator_next (iter, (void *) &key, (void *) &value) == 0)
  {
    char **temp;

    /* remove missing values when list values */
    if (value->state == STATE_MISSING)
      continue;

    if (ret_times != NULL)
    {
      cdtime_t *tmp_times;

      tmp_times = (cdtime_t *) realloc (times, sizeof (cdtime_t) * (number + 1));
      if (tmp_times == NULL)
      {
	status = -1;
	break;
      }
      times = tmp_times;
      times[number] = value->last_time;
    }

    temp = (char **) realloc (names, sizeof (char *) * (number + 1));
    if (temp == NULL)
    {
      status = -1;
      break;
    }
    names = temp;
    names[number] = strdup (key);
    if (names[number] == NULL)
    {
      status = -1;
      break;
    }
    number++;
  } /* while (c_avl_iterator_next) */

  c_avl_iterator_destroy (iter);
  pthread_mutex_unlock (&cache_lock);

  if (status != 0)
  {
    size_t i;
    
    for (i = 0; i < number; i++)
    {
      sfree (names[i]);
    }
    sfree (names);

    return (-1);
  }

  *ret_names = names;
  if (ret_times != NULL)
    *ret_times = times;
  *ret_number = number;

  return (0);
}