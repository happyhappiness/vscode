static int cache_compare (const cache_entry_t *a, const cache_entry_t *b)
{
#if COLLECT_DEBUG
  assert ((a != NULL) && (b != NULL));
#endif
  return (strcmp (a->name, b->name));
}