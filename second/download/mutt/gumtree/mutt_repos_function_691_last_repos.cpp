struct hash_elem *hash_find_bucket (const HASH *table, const char *strkey)
{
  union hash_key key;
  int hash;

  if (!table)
    return NULL;

  key.strkey = strkey;
  hash = table->gen_hash (key, table->nelem);
  return table->table[hash];
}