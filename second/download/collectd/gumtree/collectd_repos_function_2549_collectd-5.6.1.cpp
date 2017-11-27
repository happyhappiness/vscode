int meta_data_exists (meta_data_t *md, const char *key) /* {{{ */
{
  if ((md == NULL) || (key == NULL))
    return (-EINVAL);

  pthread_mutex_lock (&md->lock);

  for (meta_entry_t *e = md->head; e != NULL; e = e->next)
  {
    if (strcasecmp (key, e->key) == 0)
    {
      pthread_mutex_unlock (&md->lock);
      return (1);
    }
  }

  pthread_mutex_unlock (&md->lock);
  return (0);
}