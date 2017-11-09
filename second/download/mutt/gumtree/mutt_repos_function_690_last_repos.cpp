void *int_hash_find (const HASH *table, unsigned int intkey)
{
  union hash_key key;
  key.intkey = intkey;
  return union_hash_find (table, key);
}