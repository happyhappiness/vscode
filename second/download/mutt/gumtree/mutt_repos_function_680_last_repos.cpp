static HASH *new_hash (int nelem)
{
  HASH *table = safe_calloc (1, sizeof (HASH));
  if (nelem == 0)
    nelem = 2;
  table->nelem = nelem;
  table->table = safe_calloc (nelem, sizeof (struct hash_elem *));
  return table;
}