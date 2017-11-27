int uc_check_timeout (void)
{
  time_t now;
  cache_entry_t *ce;

  char **keys = NULL;
  int keys_len = 0;

  char *key;
  c_avl_iterator_t *iter;
  int i;
  
  pthread_mutex_lock (&cache_lock);

  now = time (NULL);

  /* Build a list of entries to be flushed */
  iter = c_avl_get_iterator (cache_tree);
  while (c_avl_iterator_next (iter, (void *) &key, (void *) &ce) == 0)
  {
    /* If entry has not been updated, add to `keys' array */
    if ((now - ce->last_update) >= (2 * ce->interval))
    {
      char **tmp;

      tmp = (char **) realloc ((void *) keys,
	  (keys_len + 1) * sizeof (char *));
      if (tmp == NULL)
      {
	ERROR ("uc_purge: realloc failed.");
	c_avl_iterator_destroy (iter);
	return (-1);
      }

      keys = tmp;
      keys[keys_len] = strdup (key);
      if (keys[keys_len] == NULL)
      {
	ERROR ("uc_check_timeout: strdup failed.");
	continue;
      }
      keys_len++;
    }
  } /* while (c_avl_iterator_next) */

  for (i = 0; i < keys_len; i++)
  {
    int status;

    status = ut_check_interesting (keys[i]);

    if (status < 0)
    {
      ERROR ("uc_check_timeout: ut_check_interesting failed.");
      sfree (keys[i]);
    }
    else if (status == 0) /* ``service'' is uninteresting */
    {
      ce = NULL;
      DEBUG ("uc_check_timeout: %s is missing but ``uninteresting''",
	  keys[i]);
      status = c_avl_remove (cache_tree, keys[i],
	  (void *) &key, (void *) &ce);
      if (status != 0)
      {
	ERROR ("uc_check_timeout: c_avl_remove (%s) failed.", keys[i]);
      }
      sfree (keys[i]);
      cache_free (ce);
    }
    else if (status == 1) /* persist */
    {
      DEBUG ("uc_check_timeout: %s is missing, sending notification.",
	  keys[i]);
      ce->state = STATE_MISSING;
    }
    else if (status == 2) /* do not persist */
    {
      if (ce->state == STATE_MISSING)
      {
	DEBUG ("uc_check_timeout: %s is missing but "
	    "notification has already been sent.",
	    keys[i]);
	sfree (keys[i]);
      }
      else /* (ce->state != STATE_MISSING) */
      {
	DEBUG ("uc_check_timeout: %s is missing, sending one notification.",
	    keys[i]);
	ce->state = STATE_MISSING;
      }
    }
    else
    {
      WARNING ("uc_check_timeout: ut_check_interesting (%s) returned ",
	  "invalid status %i.",
	  keys[i], status);
    }
  } /* for (keys[i]) */

  c_avl_iterator_destroy (iter);

  pthread_mutex_unlock (&cache_lock);

  for (i = 0; i < keys_len; i++)
  {
    if (keys[i] == NULL)
      continue;

    uc_send_notification (keys[i]);
    sfree (keys[i]);
  }

  sfree (keys);

  return (0);
}