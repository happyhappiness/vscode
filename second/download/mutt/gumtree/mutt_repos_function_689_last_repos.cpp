struct hash_elem *hash_find_elem (const HASH *table, const char *strkey)
{
  union hash_key key;
  key.strkey = strkey;
  return union_hash_find_elem (table, key);
}