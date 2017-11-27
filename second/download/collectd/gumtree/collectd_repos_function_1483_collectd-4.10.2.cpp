void meta_data_destroy (meta_data_t *md) /* {{{ */
{
  if (md == NULL)
    return;

  md_entry_free (md->head);
  free (md);
}