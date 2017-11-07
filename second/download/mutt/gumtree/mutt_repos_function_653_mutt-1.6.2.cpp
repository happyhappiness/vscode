void *hash_find_hash (const HASH * table, int hash, const char *key)
{
  struct hash_elem *ptr = table->table[hash];
  for (; ptr; ptr = ptr->next)
  {
    if (table->cmp_string (key, ptr->key) == 0)
      return (ptr->data);
  }
  return NULL;
}