void fbh_destroy (fbhash_t *h) /* {{{ */
{
  if (h == NULL)
    return;

  free (h->filename);
  fbh_free_tree (h->tree);
}