int meta_data_type (meta_data_t *md, const char *key) /* {{{ */
{
  if ((md == NULL) || (key == NULL))
    return -EINVAL;

  pthread_mutex_lock (&md->lock);

  for (meta_entry_t *e = md->head; e != NULL; e = e->next)
  {
    if (strcasecmp (key, e->key) == 0)
    {
      pthread_mutex_unlock (&md->lock);
      return e->type;
    }
  }

  pthread_mutex_unlock (&md->lock);
  return 0;
}