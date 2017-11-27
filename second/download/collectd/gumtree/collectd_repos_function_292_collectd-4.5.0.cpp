static void cache_free (cache_entry_t *ce)
{
  if (ce == NULL)
    return;

  sfree (ce->values_gauge);
  sfree (ce->values_counter);
  sfree (ce);
}