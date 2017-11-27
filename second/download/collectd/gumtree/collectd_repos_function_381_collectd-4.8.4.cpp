static void cache_free (cache_entry_t *ce)
{
  if (ce == NULL)
    return;

  sfree (ce->values_gauge);
  sfree (ce->values_raw);
  sfree (ce->history);
  if (ce->meta != NULL)
  {
    meta_data_destroy (ce->meta);
    ce->meta = NULL;
  }
  sfree (ce);
}