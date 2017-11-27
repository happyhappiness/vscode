void uc_iterator_destroy (uc_iter_t *iter)
{
  if (iter == NULL)
    return;

  c_avl_iterator_destroy (iter->iter);
  pthread_mutex_unlock (&cache_lock);

  free (iter);
}