int meta_data_clone_merge (meta_data_t **dest, meta_data_t *orig) /* {{{ */
{
  if (orig == NULL)
    return (0);

  if (*dest == NULL) {
    *dest = meta_data_clone(orig);
    return(0);
  }

  pthread_mutex_lock (&orig->lock);
  for (meta_entry_t *e=orig->head; e != NULL; e = e->next)
  {
    md_entry_insert_clone((*dest), e);
  }
  pthread_mutex_unlock (&orig->lock);

  return (0);
}