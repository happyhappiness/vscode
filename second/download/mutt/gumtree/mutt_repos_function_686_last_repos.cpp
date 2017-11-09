static struct hash_elem *union_hash_find_elem (const HASH *table, union hash_key key)
{
  int hash;
  struct hash_elem *ptr;

  if (!table)
    return NULL;

  hash = table->gen_hash (key, table->nelem);
  ptr = table->table[hash];
  for (; ptr; ptr = ptr->next)
  {
    if (table->cmp_key (key, ptr->key) == 0)
      return (ptr);
  }
  return NULL;
}