HASH *hash_create (int nelem)
{
  HASH *table = safe_malloc (sizeof (HASH));
  if (nelem == 0)
    nelem = 2;
  table->nelem = nelem;
  table->table = safe_calloc (nelem, sizeof (struct hash_elem *));
  return table;
}