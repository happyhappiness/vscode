void int_hash_delete (HASH *table, unsigned int intkey, const void *data,
                  void (*destroy) (void *))
{
  union hash_key key;
  key.intkey = intkey;
  union_hash_delete (table, key, data, destroy);
}