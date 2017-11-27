void fbh_destroy (fbhash_t *h) /* {{{ */
{
  if (h == NULL)
    return;

  pthread_mutex_destroy (&h->lock);
  free (h->filename);
  fbh_free_tree (h->tree);
}