meta_data_t *meta_data_clone(meta_data_t *orig) /* {{{ */
{
  meta_data_t *copy;

  if (orig == NULL)
    return (NULL);

  copy = meta_data_create();
  if (copy == NULL)
    return (NULL);

  pthread_mutex_lock(&orig->lock);
  copy->head = md_entry_clone(orig->head);
  pthread_mutex_unlock(&orig->lock);

  return (copy);
}