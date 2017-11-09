int int_hash_insert (HASH * table, unsigned int intkey, void *data)
{
  union hash_key key;
  key.intkey = intkey;
  return union_hash_insert (table, key, data);
}