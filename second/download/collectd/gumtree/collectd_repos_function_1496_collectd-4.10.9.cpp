void meta_data_destroy (meta_data_t *md) /* {{{ */
{
  if (md == NULL)
    return;

  pthread_mutex_destroy(&md->lock);
  md_entry_free (md->head);
  pthread_mutex_destroy (&md->lock);
  free (md);
}