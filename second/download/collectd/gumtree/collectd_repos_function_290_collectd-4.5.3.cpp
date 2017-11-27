static int cache_compare (const cache_entry_t *a, const cache_entry_t *b)
{
  assert ((a != NULL) && (b != NULL));
  return (strcmp (a->name, b->name));
}