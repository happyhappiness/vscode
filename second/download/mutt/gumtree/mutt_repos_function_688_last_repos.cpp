void *hash_find (const HASH *table, const char *strkey)
{
  union hash_key key;
  key.strkey = strkey;
  return union_hash_find (table, key);
}