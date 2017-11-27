char *fbh_get (fbhash_t *h, const char *key) /* {{{ */
{
  char *value;
  char *value_copy;
  int status;

  if ((h == NULL) || (key == NULL))
    return (NULL);

  value = NULL;
  value_copy = NULL;

  pthread_mutex_lock (&h->lock);

  /* TODO: Checking this everytime may be a bit much..? */
  fbh_check_file (h);

  status = c_avl_get (h->tree, key, (void *) &value);
  if (status == 0)
  {
    assert (value != NULL);
    value_copy = strdup (value);
  }

  pthread_mutex_unlock (&h->lock);

  return (value_copy);
}